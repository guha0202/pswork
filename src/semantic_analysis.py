import os
import re

class Token:
    def __init__(self, type_id, value):
        self.type_id = type_id
        self.value = value

    def __repr__(self):
        return f'<{self.type_id}, "{self.value}">'

class SyntaxError(Exception):
    def __init__(self, message, position):
        self.message = message
        self.position = position

    def __str__(self):
        return f"SyntaxError: {self.message} at token {self.position}"

class SemanticAnalyzer:
    def __init__(self, tokens):
        self.tokens = tokens
        self.position = 0
        self.current_token = self.tokens[self.position]
        self.temp_count = 0
        self.label_count = 0
        self.intermediate_code = []

    def advance(self):
        self.position += 1
        if self.position < len(self.tokens):
            self.current_token = self.tokens[self.position]
        else:
            self.current_token = None

    def analyze(self):
        try:
            self.program()
            if self.current_token is not None:
                raise SyntaxError("Unexpected token", self.position)
            print("通过语义分析")
        except SyntaxError as e:
            print(e)

    def program(self):
        while self.current_token is not None:
            self.statement()

    def statement(self):
        if self.current_token.type_id == 1:  # KEYWORD
            if self.current_token.value in ["float", "char"]:
                self.floatchardeclaration()
            elif self.current_token.value == "int":
                self.intdeclaration()
            elif self.current_token.value == "if":
                self.if_statement()
            elif self.current_token.value == "while":
                self.while_statement()
            elif self.current_token.value == "return":
                self.return_statement()
            elif self.current_token.value == "main":
                self.main_function()
            else:
                raise SyntaxError(f"Unexpected keyword {self.current_token.value}", self.position)
        else:
            self.expression_statement()

    def intdeclaration(self):
        self.advance()  # Skip type
        if self.current_token.type_id != 2 and self.current_token.value != "main":  # IDENTIFIER OR MAIN
            raise SyntaxError("Expected identifier after type", self.position)
        elif self.current_token.value == "main":
            self.main_function()
        else:
            self.advance()
            if self.current_token.value not in [";", "="]:
                raise SyntaxError("Expected ';' after declaration", self.position)
            elif self.current_token.value == "=":
                self.advance()
                self.expression()
            if self.current_token.value != ";":
                raise SyntaxError("Expected ';' after declaration", self.position)
        self.advance()

    def floatchardeclaration(self):
        self.advance()  # Skip type
        if self.current_token.type_id != 2:  # IDENTIFIER
            raise SyntaxError("Expected identifier after type", self.position)
        self.advance()
        if self.current_token.value not in [";", "="]:
            raise SyntaxError("Expected ';' after declaration", self.position)
        elif self.current_token.value == "=":
            self.advance()
            self.expression()
        if self.current_token.value != ";":
            raise SyntaxError("Expected ';' after declaration", self.position)
        self.advance()

    def if_statement(self):
        self.advance()  # Skip 'if'
        if self.current_token.value != "(":
            raise SyntaxError("Expected '(' after 'if'", self.position)
        self.advance()
        condition_true_label = f"L{self.label_count}"
        self.label_count += 1
        self.expression()
        self.intermediate_code.append(('JZ', self.current_token.value, condition_true_label))
        if self.current_token.value != ")":
            raise SyntaxError("Expected ')' after condition", self.position)
        self.advance()
        if self.current_token.value != "{":
            raise SyntaxError("Expected '{' after 'if()'", self.position)
        self.advance()
        while self.current_token and self.current_token.value != "}":
            self.statement()
        if self.current_token is None or self.current_token.value != "}":
            raise SyntaxError("Expected '}' after if body", self.position)
        self.advance()
        if self.current_token and self.current_token.value == "else":
            else_label = f"L{self.label_count}"
            self.label_count += 1
            self.intermediate_code.append(('JMP', '', else_label))
            self.intermediate_code.append(('LABEL', '', condition_true_label))
            self.advance()
            if self.current_token.value != "{":
                raise SyntaxError("Expected '{' after 'if()'", self.position)
            self.advance()
            while self.current_token and self.current_token.value != "}":
                self.statement()
                self.intermediate_code.append(('LABEL', '', else_label))
                self.intermediate_code.append(('LABEL', '', condition_true_label))
            if self.current_token is None or self.current_token.value != "}":
                raise SyntaxError("Expected '}' after if body", self.position)
            self.advance()

    def while_statement(self):
        self.advance()  # Skip 'while'
        condition_start_label = f"L{self.label_count}"
        self.label_count += 1
        self.intermediate_code.append(('LABEL', '', condition_start_label))
        if self.current_token.value != "(":
            raise SyntaxError("Expected '(' after 'while'", self.position)
        self.advance()
        condition_true_label = f"L{self.label_count}"
        self.label_count += 1
        self.expression()
        self.intermediate_code.append(('JZ', self.current_token.value, condition_true_label))
        if self.current_token.value != ")":
            raise SyntaxError("Expected ')' after condition", self.position)
        self.advance()
        if self.current_token.value != "{":
            raise SyntaxError("Expected '{' after 'while()'", self.position)
        self.advance()
        while self.current_token and self.current_token.value != "}":
            self.statement()
            self.intermediate_code.append(('JMP', '', condition_start_label))
            self.intermediate_code.append(('LABEL', '', condition_true_label))
        if self.current_token is None or self.current_token.value != "}":
            raise SyntaxError("Expected '}' after while body", self.position)
        self.advance()

    def return_statement(self):
        self.advance()  # Skip 'return'
        self.expression()
        if self.current_token.value != ";":
            raise SyntaxError("Expected ';' after return expression", self.position)
        self.advance()

    def main_function(self):
        self.advance()  # Skip 'main'
        if self.current_token.value != "(":
            raise SyntaxError("Expected '(' after 'main'", self.position)
        self.advance()
        if self.current_token.value != ")":
            raise SyntaxError("Expected ')' after 'main('", self.position)
        self.advance()
        if self.current_token.value != "{":
            raise SyntaxError("Expected '{' after 'main()'", self.position)
        self.advance()
        while self.current_token and self.current_token.value != "}":
            self.statement()
        if self.current_token is None or self.current_token.value != "}":
            raise SyntaxError("Expected '}' after main function body", self.position)
        self.advance()

    def expression_statement(self):
        self.expression()
        if self.current_token.value != ";":
            raise SyntaxError("Expected ';' after expression", self.position)
        self.advance()

    def expression(self):
        self.assignment()

    def assignment(self):
        result = self.logical_or()
        if self.current_token and self.current_token.value == "=":
            self.advance()
            rhs = self.assignment()
            self.intermediate_code.append(("=", result, rhs, result))
        return result

    def logical_or(self):
        result = self.logical_and()
        while self.current_token and self.current_token.value == "||":
            self.advance()
            rhs = self.logical_and()
            result = self.new_temp()
            self.intermediate_code.append(("||", result, rhs, result))
        return result

    def logical_and(self):
        result = self.equality()
        while self.current_token and self.current_token.value == "&&":
            self.advance()
            rhs = self.equality()
            result = self.new_temp()
            self.intermediate_code.append(("&&", result, rhs, result))
        return result

    def equality(self):
        result = self.relational()
        while self.current_token and self.current_token.value in ["==", "!="]:
            operator = self.current_token.value
            self.advance()
            rhs = self.relational()
            temp = self.new_temp()
            self.intermediate_code.append((operator, result, rhs, temp))
            result = temp
        return result

    def relational(self):
        result = self.additive()
        while self.current_token and self.current_token.value in ["<", ">"]:
            operator = self.current_token.value
            self.advance()
            rhs = self.additive()
            temp = self.new_temp()
            self.intermediate_code.append((operator, result, rhs, temp))
            result = temp
        return result

    def additive(self):
        result = self.multiplicative()
        while self.current_token and self.current_token.value in ["+", "-"]:
            operator = self.current_token.value
            self.advance()
            rhs = self.multiplicative()
            temp = self.new_temp()
            self.intermediate_code.append((operator, result, rhs, temp))
            result = temp
        return result

    def multiplicative(self):
        result = self.unary()
        while self.current_token and self.current_token.value in ["*", "/"]:
            operator = self.current_token.value
            self.advance()
            rhs = self.unary()
            temp = self.new_temp()
            self.intermediate_code.append((operator, result, rhs, temp))
            result = temp
        return result

    def unary(self):
        if self.current_token and self.current_token.value == "!":
            self.advance()
            result = self.unary()
            temp = self.new_temp()
            self.intermediate_code.append(("!", result, "", temp))
            return temp
        return self.primary()

    def primary(self):
        if self.current_token.type_id in [2, 3, 4, 5]:  # IDENTIFIER, INTEGER, FLOAT, CHARACTER
            result = self.current_token.value
            self.advance()
            return result
        elif self.current_token.value == "(":
            self.advance()
            result = self.expression()
            if self.current_token.value != ")":
                raise SyntaxError("Expected ')' after expression", self.position)
            self.advance()
            return result
        else:
            raise SyntaxError("Unexpected token", self.position)

    def new_temp(self):
        self.temp_count += 1
        return f"T{self.temp_count}"

    def generate_intermediate_code(self):
        return self.intermediate_code

if __name__ == "__main__":
    base_dir = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
    output_dir = os.path.join(base_dir, 'output')
    token_file = os.path.join(output_dir, 'Token.txt')
    intermediate_code_file = os.path.join(output_dir, 'intermediate_code.txt')

    token_pattern = re.compile(r"<(\d+), \"(.*?)\">")

    tokens = []
    with open(token_file, 'r') as f:
        for line in f:
            match = token_pattern.match(line.strip())
            if match:
                type_id = int(match.group(1))
                value = match.group(2)
                tokens.append(Token(type_id, value))

    analyzer = SemanticAnalyzer(tokens)
    analyzer.analyze()

    intermediate_code = analyzer.generate_intermediate_code()
    with open(intermediate_code_file, 'w') as f:
        for code in intermediate_code:
            f.write(f'{code}\n')

    print(f'Intermediate code written to {intermediate_code_file}')
