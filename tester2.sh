#!/bin/bash

# Simple tester for bash --posix vs minishell

TESTS=()

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

# Tokens to filter out (add/remove entries as needed)
FILTER_TOKENS=(
    "bash-5.1$"
    "minishell$"
)

# Initialize logging
init_logging() {
    # Create tests directory if it doesn't exist
    mkdir -p tests
    
    # Find next test run number
    TEST_RUN_NUM=1
    while [ -d "tests/$TEST_RUN_NUM" ]; do
        ((TEST_RUN_NUM++))
    done
    
    # Create test run directory
    TEST_DIR="tests/$TEST_RUN_NUM"
    mkdir -p "$TEST_DIR"
    
    # Initialize main log file
    LOG_FILE="$TEST_DIR/test_results.log"
    echo "SHELL COMPARISON TESTS" > "$LOG_FILE"
    echo "Date: $(date)" >> "$LOG_FILE"
    echo "Test Run: $TEST_RUN_NUM" >> "$LOG_FILE"
    echo >> "$LOG_FILE"
    
    echo -e "${BOLD}${GREEN}=== SHELL COMPARISON TESTS ===${NC}"
    echo -e "${YELLOW}Date: $(date)${NC}"
    echo -e "${CYAN}Logging to: $TEST_DIR${NC}"
    echo
}

add_test() {
    TESTS+=("$1")
}

clean_output() {
    local output="$1"
    
    # Remove ANSI escape sequences and control characters
    output=$(echo "$output" | sed 's/\x1b\[[0-9;]*[a-zA-Z]//g')
    output=$(echo "$output" | sed 's/\x1b\[[?][0-9]*[a-zA-Z]//g')
    output=$(echo "$output" | tr -d '\r')
    
    # Remove prompts using more flexible patterns
    # Remove bash prompts (with or without trailing spaces/newlines)
    output=$(echo "$output" | sed 's/^bash-5\.2\$[[:space:]]*$//g')
    output=$(echo "$output" | sed 's/bash-5\.2\$[[:space:]]*//g')
    
    # Remove minishell prompts (with or without trailing spaces/newlines)
    output=$(echo "$output" | sed 's/^minishell\$[[:space:]]*$//g')
    output=$(echo "$output" | sed 's/minishell\$[[:space:]]*//g')
    
    # Remove error message prefixes - both uppercase and lowercase
    output=$(echo "$output" | sed 's/^bash:[[:space:]]*//g')
    output=$(echo "$output" | sed 's/bash:[[:space:]]*//g')
    output=$(echo "$output" | sed 's/^Minishell[[:space:]]*:[[:space:]]*//g')
    output=$(echo "$output" | sed 's/Minishell[[:space:]]*:[[:space:]]*//g')
    output=$(echo "$output" | sed 's/^minishell[[:space:]]*:[[:space:]]*//g')
    output=$(echo "$output" | sed 's/minishell[[:space:]]*:[[:space:]]*//g')
    
    # Remove completely empty lines
    echo "$output" #| sed '/^[[:space:]]*$/d'
}
normalize_output() {
    sed 's/^[[:space:]]*//;s/[[:space:]]*$//' | sed '/^$/d'
}

extract_real_output() {
    local input="$1"
    local cmd="$2"
    local cleaned="$input"
    # Pour chaque ligne de la commande, on la supprime de la sortie
    while IFS= read -r line; do
        cleaned=$(echo "$cleaned" | grep -v -e "^$line$")
    done <<< "$cmd"
    # Supprime aussi les lignes 'echo $?' et 'echo $?'
    cleaned=$(echo "$cleaned" | grep -v -e "^echo \$\?$")
    echo "$cleaned"
}

run_test() {
    local cmd="$1"
    local test_num="$2"
    
    # Display to terminal with colors
    echo -e "${BOLD}${BLUE}$━━━ Test $test_num: ━━━$ \n ${YELLOW}$cmd\n${BLUE}$━━━ ━━━ ━━━ ━━━$ ${NC}"
    
    # Log to file without colors
    #echo "━━━ Test $test_num: $cmd ━━━" >> "$LOG_FILE"
    
    # Get bash output with selective logging  
		bash_raw=$(expect -c "
    set timeout 5
    log_user 0
    spawn bash --posix
    expect \"$ \"
    log_user 1
$(echo "$cmd" | while IFS= read -r line; do
    if [[ -n "$line" ]]; then
        echo "    send {${line}}"
        echo "    send \"\\r\""
        echo "    expect \"$ \""
    fi
done)
    send \"echo \$?\"
    send \"\\r\"
    expect \"$ \"
    log_user 0
    send \"exit\\r\"
    expect eof
" 2>/dev/null)
    
    # Get minishell output with selective logging and timeout
    minishell_raw=$(expect -c "
    set timeout 5
    log_user 0
    spawn ./minishell
    expect \"$ \"
    log_user 1
$(echo "$cmd" | while IFS= read -r line; do
    if [[ -n "$line" ]]; then
        echo "    send {${line}}"
        echo "    send \"\\r\""
        echo "    expect \"$ \""
    fi
done)
    send \"echo \$?\"
    send \"\\r\"
    expect \"$ \"
    log_user 0
    send \"exit\\r\"
    expect eof
" 2>/dev/null)

    
    

   # Clean outputs
    bash_output=$(clean_output "$bash_raw")
    minishell_output=$(clean_output "$minishell_raw")

    # Extrait uniquement ce qui vient après le prompt
    # Supprime la ligne de la commande et de echo $?
    bash_clean=$(extract_real_output "$bash_output" "$cmd")
    minishell_clean=$(extract_real_output "$minishell_output" "$cmd")



    # Affichage

    # Compare and show result
    # Compare and show result
    
    bash_clean=$(echo "$bash_clean" | normalize_output)
    minishell_clean=$(echo "$minishell_clean" | normalize_output)


    if [ "$bash_clean" = "$minishell_clean" ]; then
        echo -e "${GREEN}✓ MATCH${NC}"
        echo -e "$cmd" >> "$TEST_DIR/MATCH.txt"
    else
        echo -e "${RED}✗ DIFFER${NC}"
        echo -e "$cmd" >> "$TEST_DIR/DIFFER.txt"
        {
            echo "━━━ Test $test_num: $cmd ━━━"
            echo "BASH:"
            echo "$bash_clean"
            echo
            echo "MINISHELL:"
            echo "$minishell_clean"
            echo
            echo "✗ DIFFER"
            echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
            echo
        } >> "$LOG_FILE"
    fi
    # -------------------------
    # Valgrind memory leak check
    # -------------------------
    valgrind_output=$(valgrind --suppressions=valgrind.supp --leak-check=full  --log-fd=1 ./minishell 2>&1 <<EOF
$cmd
exit
EOF
)

    if echo "$valgrind_output" | grep -q "definitely lost: [1-9][0-9]* bytes"; then
        echo -e "${YELLOW}⚠️  MEMORY LEAK DETECTED${NC}"
        {
            echo "⚠️  MEMORY LEAK DETECTED"
            echo "$valgrind_output"
            echo
        } >> "$LOG_FILE"
    else
        echo -e "${GREEN}✓ NO LEAK${NC}"
    fi

}

# Add your tests here:
read_tests() {
    local test=""
    while IFS= read -r line || [ -n "$line" ]; do
        if [[ -z "$line" ]]; then
            if [[ -n "$test" ]]; then
                TESTS+=("$test")
                test=""
            fi
        else
            test="${test}${line}"$'\n'
        fi
    done < tmp.txt  # ← C’est ici qu’on lit le fichier
    if [[ -n "$test" ]]; then
        TESTS+=("$test")
    fi
}

read_tests  # On remplit le tableau TESTS à partir du fichier



# Initialize logging before running tests
init_logging

# Run all tests
test_num=1
for cmd in "${TESTS[@]}"; do
    run_test "$cmd" "$test_num"
    test_num=$((test_num + 1))
done

echo -e "${BOLD}${GREEN}=== TESTS COMPLETE ===${NC}"
echo "TESTS COMPLETE" >> "$LOG_FILE"
echo -e "${CYAN}Results saved to: $TEST_DIR${NC}"