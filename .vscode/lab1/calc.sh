#!/bin/bash

# File để lưu trữ giá trị ANS
ANS_FILE="ans_value.txt"

# Initialize ANS and history
ANS=0
history=()

# Đọc giá trị ANS từ file nếu nó tồn tại
if [ -f "$ANS_FILE" ]; then
    ANS=$(<"$ANS_FILE")
fi

# Function to perform calculations
calculate() {
    local a=$1
    local operator=$2
    local b=$3

    # Replace 'ANS' with the current value of ANS
    if [ "$a" == "ANS" ]; then a=$ANS; fi
    if [ "$b" == "ANS" ]; then b=$ANS; fi

    # Validate that inputs are numbers
    if ! [[ "$a" =~ ^-?[0-9]+(\.[0-9]+)?$ ]] || ! [[ "$b" =~ ^-?[0-9]+(\.[0-9]+)?$ ]]; then
        echo "SYNTAX ERROR"
        return 1
    fi

    # Perform the calculation
    case $operator in
        +) result=$(echo "$a + $b" | bc);;
        -) result=$(echo "$a - $b" | bc);;
        x|\*) result=$(echo "$a * $b" | bc);;
        /) 
            if [ "$b" == "0" ]; then
                echo "MATH ERROR"
                return 1
            fi
            # Perform the division and round to 2 decimal places
            result=$(echo "scale=3; $a / $b" | bc)
            result=$(printf "%.2f" "$result")
            ;;
        %) result=$(echo "$a % $b" | bc);;
        *) echo "SYNTAX ERROR"; return 1;;
    esac

    # Store result in ANS and update history
    ANS=$result
    history+=("$a $operator $b = $result")

    # Keep only the last 5 entries in history
    if [ ${#history[@]} -gt 5 ]; then
        history=("${history[@]:1}")
    fi

    echo "$result"
}

# Main loop
while true; do
    echo -n ">> "

    # Read input from user
    read input

    # Convert input to uppercase to handle EXIT/HIST cases
    case ${input^^} in
        "EXIT")
            # Lưu giá trị ANS vào file trước khi thoát
            echo "$ANS" > "$ANS_FILE"
            break
            ;;
        "HIST")
            for entry in "${history[@]}"; do
                echo "$entry"
            done
            continue
            ;;
    esac

    # Parse input using spaces as separators
    set -- $input

    # Ensure exactly three components (e.g., 2 + 5)
    if [ $# -ne 3 ]; then
        echo "SYNTAX ERROR"
        continue
    fi

    # Call the calculate function with parsed components
    calculate "$1" "$2" "$3"
done
