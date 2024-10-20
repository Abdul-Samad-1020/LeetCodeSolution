class Solution {
public:
    bool parseBoolExpr(string expression) {
        return evaluate(expression, 0).first; // Get the boolean value from the evaluation
    }

private:
    pair<bool, int> evaluate(const string& expr, int start) {
        if (expr[start] == 't') return {true, start + 1}; // 't' evaluates to true
        if (expr[start] == 'f') return {false, start + 1}; // 'f' evaluates to false

        char operation = expr[start]; // Get the operation ('!', '&', '|')
        start += 2; // Move past the operation and the opening parenthesis

        vector<bool> results; // To store results of inner expressions

        while (expr[start] != ')') {
            auto [result, nextStart] = evaluate(expr, start); // Recursively evaluate inner expression
            results.push_back(result);
            start = nextStart; // Move to the next character after the evaluated expression

            if (expr[start] == ',') start++; // Skip the comma
        }

        // Now we are at the closing parenthesis
        bool finalResult = false;
        if (operation == '!') {
            finalResult = !results[0]; // NOT operation
        } else if (operation == '&') {
            finalResult = all_of(results.begin(), results.end(), [](bool val) { return val; }); // AND operation
        } else if (operation == '|') {
            finalResult = any_of(results.begin(), results.end(), [](bool val) { return val; }); // OR operation
        }

        return {finalResult, start + 1}; // Return the result and move past the closing parenthesis
    }
};