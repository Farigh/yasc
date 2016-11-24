#! /bin/bash

unit_test_runtime=$1
if [ "${unit_test_runtime}" == "" ]; then
    echo "Usage: $0 <unit_test_runtime>"
    exit 1
fi

# Enable colors only is in interactive shell
if [ -t 1 ]; then
    RESET_COLOR=$(echo -e '\e[00m')
    LIGHT_RED=$(echo -e '\e[1;31m')
    LIGHT_GREEN=$(echo -e '\e[1;32m')
    PURPLE=$(echo -e '\e[0;35m')
    CYAN=$(echo -e '\e[0;36m')
fi

echo ""

total_test_failed=0
total_test_succeeded=0
current_suite_test_failed=0
current_suite_test_succeeded=0
current_suite_name=""
while read -r test_line; do
    # Test suite begin
    if [[ "${test_line}" == "Test suite:"* ]] || [ "${test_line}" == "Test suite end" ]; then
        # Previous test suite end
        if [ "${current_suite_name}" != "" ]; then
            # Print results
            echo "**** Results:"
            echo "**    Suite test count: $(($current_suite_test_failed + $current_suite_test_succeeded))"
            echo "** Suite success count: $current_suite_test_succeeded"

            failure_color=""
            if [ ${current_suite_test_failed} -ne 0 ]; then
                failure_color="${LIGHT_RED}"
            fi

            echo "** Suite failure count: ${failure_color}${current_suite_test_failed}${RESET_COLOR}"
            echo "****"
            echo "******** End of suite > ${current_suite_name}"
        fi

        current_suite_test_failed=0
        current_suite_test_succeeded=0
        current_suite_name=$(echo ${test_line} | sed "s/^Test suite: //")

        if [ "${test_line}" != "Test suite end" ]; then
            echo "**** Begin of suite ${PURPLE}${current_suite_name}${RESET_COLOR}"
        fi
    elif [[ "${test_line}" == "Test:"* ]]; then
        current_test_name=$(echo ${test_line} | sed "s/^Test: ${current_suite_name}:://")
        echo "** Running test ${CYAN}${current_test_name}${RESET_COLOR}"
        $unit_test_runtime "${current_suite_name}::${current_test_name}"
        # Check return value
        result_str="${LIGHT_GREEN}PASS${RESET_COLOR}"
        if [ $? -ne 0 ]; then
            result_str="${LIGHT_RED}FAIL${RESET_COLOR}"
            ((total_test_failed++))
            ((current_suite_test_failed++))
        else
            ((total_test_succeeded++))
            ((current_suite_test_succeeded++))
        fi
        echo "** Done [${result_str}]"
    fi
done < <($unit_test_runtime -l; echo -e "\nTest suite end")


# Print summary if available
if [ $(($total_test_failed + $total_test_succeeded)) -ne 0 ]; then
    final_result_str="${LIGHT_GREEN}PASS${RESET_COLOR}"
    if [ $total_test_failed -ne 0 ]; then
        final_result_str="${LIGHT_RED}FAIL${RESET_COLOR}"
    fi
    echo ""
    echo ""
    echo "**** Summary [${final_result_str}]"
    echo "**    Total test count: $(($total_test_failed + $total_test_succeeded))"
    echo "** Total success count: $total_test_succeeded"

    failure_color=""
    if [ ${total_test_failed} -ne 0 ]; then
        failure_color="${LIGHT_RED}"
    fi

    echo "** Total failure count: ${failure_color}${total_test_failed}${RESET_COLOR}"
    echo "********"
fi
