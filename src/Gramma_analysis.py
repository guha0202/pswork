import os
import re
import json

class Token:
    def __init__(self, type_id, value):
        self.type_id = type_id
        self.value = value

    def __repr__(self):
        return f'<{self.type_id}, "{self.value}">'

class TreeNode:
    def __init__(self, value):
        self.value = value
        self.children = []

    def add_child(self, node):
        self.children.append(node)

    def __str__(self, level=0):
        ret = "\t" * level + repr(self.value) + "\n"
        for child in self.children:
            ret += child.__str__(level + 1)
        return ret

    def __repr__(self):
        return self.__str__()

class SyntaxError(Exception):
    def __init__(self, message, position):
        self.message = message
        self.position = position
        super().__init__(self.message)

    def __str__(self):
        return f"SyntaxError: {self.message} at position {self.position}"

class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.position = 0
        self.current_token = self.tokens[self.position]
        self.root = TreeNode("Program")

    def advance(self):
        self.position += 1
        if self.position < len(self.tokens):
            self.current_token = self.tokens[self.position]
        else:
            self.current_token = None

    def parse(self):
        try:
            self.program(self.root)
            if self.current_token is not None:
                raise SyntaxError("Unexpected token", self.position)
            print("通过语法分析")
            self.print_syntax_tree()
        except SyntaxError as e:
            print(e)

    def program(self, parent_node):
        while self.current_token is not None:
            self.statement(parent_node)

    def statement(self, parent_node):
        node = TreeNode("Statement")
        parent_node.add_child(node)
        if self.current_token.type_id == 1:  # KEYWORD
            if self.current_token.value in ["float", "char"]:
                self.floatchardeclaration(node)
            elif self.current_token.value == "int":
                self.intdeclaration(node)
            elif self.current_token.value == "if":
                self.if_statement(node)
            elif self.current_token.value == "while":
                self.while_statement(node)
            elif self.current_token.value == "return":
                self.return_statement(node)
            elif self.current_token.value == "main":
                self.main_function(node)
            else:
                raise SyntaxError(f"Unexpected keyword {self.current_token.value}", self.position)
        else:
            self.expression_statement(node)

    def intdeclaration(self, parent_node):
        node = TreeNode("IntDeclaration")
        parent_node.add_child(node)
        self.advance()  # Skip type
        if self.current_token.type_id != 2 and self.current_token.value != "main":  # IDENTIFIER OR MAIN
            raise SyntaxError("Expected identifier after type", self.position)
        elif self.current_token.value == "main":
            self.main_function(node)
        else:
            id_node = TreeNode(self.current_token.value)
            node.add_child(id_node)
            self.advance()
            if self.current_token.value not in [";", "="]:
                raise SyntaxError("Expected ';' after declaration", self.position)
            elif self.current_token.value == "=":
                eq_node = TreeNode("=")
                node.add_child(eq_node)
                self.advance()
                self.expression(node)
            if self.current_token.value != ";":
                raise SyntaxError("Expected ';' after declaration", self.position)
        self.advance()

    def floatchardeclaration(self, parent_node):
        node = TreeNode("FloatCharDeclaration")
        parent_node.add_child(node)
        self.advance()  # Skip type
        if self.current_token.type_id != 2:  # IDENTIFIER
            raise SyntaxError("Expected identifier after type", self.position)
        id_node = TreeNode(self.current_token.value)
        node.add_child(id_node)
        self.advance()
        if self.current_token.value not in [";", "="]:
            raise SyntaxError("Expected ';' after declaration", self.position)
        elif self.current_token.value == "=":
            eq_node = TreeNode("=")
            node.add_child(eq_node)
            self.advance()
            self.expression(node)
        if self.current_token.value != ";":
            raise SyntaxError("Expected ';' after declaration", self.position)
        self.advance()

    def if_statement(self, parent_node):
        node = TreeNode("IfStatement")
        parent_node.add_child(node)
        self.advance()  # Skip 'if'
        if self.current_token.value != "(":
            raise SyntaxError("Expected '(' after 'if'", self.position)
        self.advance()
        self.expression(node)
        if self.current_token.value != ")":
            raise SyntaxError("Expected ')' after condition", self.position)
        self.advance()
        if self.current_token.value != "{":
            raise SyntaxError("Expected '{' after 'if()'", self.position)
        self.advance()
        while self.current_token and self.current_token.value != "}":
            self.statement(node)
        if self.current_token is None or self.current_token.value != "}":
            raise SyntaxError("Expected '}' after if body", self.position)
        self.advance()
        if self.current_token and self.current_token.value == "else":
            else_node = TreeNode("ElseStatement")
            node.add_child(else_node)
            self.advance()
            if self.current_token.value != "{":
                raise SyntaxError("Expected '{' after 'else'", self.position)
            self.advance()
            while self.current_token and self.current_token.value != "}":
                self.statement(else_node)
            if self.current_token is None or self.current_token.value != "}":
                raise SyntaxError("Expected '}' after else body", self.position)
            self.advance()

    def while_statement(self, parent_node):
        node = TreeNode("WhileStatement")
        parent_node.add_child(node)
        self.advance()  # Skip 'while'
        if self.current_token.value != "(":
            raise SyntaxError("Expected '(' after 'while'", self.position)
        self.advance()
        self.expression(node)
        if self.current_token.value != ")":
            raise SyntaxError("Expected ')' after condition", self.position)
        self.advance()
        if self.current_token.value != "{":
            raise SyntaxError("Expected '{' after 'while()'", self.position)
        self.advance()
        while self.current_token and self.current_token.value != "}":
            self.statement(node)
        if self.current_token is None or self.current_token.value != "}":
            raise SyntaxError("Expected '}' after while body", self.position)
        self.advance()

    def return_statement(self, parent_node):
        node = TreeNode("ReturnStatement")
        parent_node.add_child(node)
        self.advance()  # Skip 'return'
        self.expression(node)
        if self.current_token.value != ";":
            raise SyntaxError("Expected ';' after return expression", self.position)
        self.advance()

    def main_function(self, parent_node):
        node = TreeNode("MainFunction")
        parent_node.add_child(node)
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
            self.statement(node)
        if self.current_token is None or self.current_token.value != "}":
            raise SyntaxError("Expected '}' after main function body", self.position)
        self.advance()

    def expression_statement(self, parent_node):
        node = TreeNode("ExpressionStatement")
        parent_node.add_child(node)
        self.expression(node)
        if self.current_token.value != ";":
            raise SyntaxError("Expected ';' after expression", self.position)
        self.advance()

    def expression(self, parent_node):
        self.assignment(parent_node)

    def assignment(self, parent_node):
        self.logical_or(parent_node)
        if self.current_token and self.current_token.value == "=":
            eq_node = TreeNode("=")
            parent_node.add_child(eq_node)
            self.advance()
            self.assignment(eq_node)

    def logical_or(self, parent_node):
        self.logical_and(parent_node)
        while self.current_token and self.current_token.value == "||":
            or_node = TreeNode("||")
            parent_node.add_child(or_node)
            self.advance()
            self.logical_and(or_node)

    def logical_and(self, parent_node):
        self.equality(parent_node)
        while self.current_token and self.current_token.value == "&&":
            and_node = TreeNode("&&")
            parent_node.add_child(and_node)
            self.advance()
            self.equality(and_node)

    def equality(self, parent_node):
        self.relational(parent_node)
        while self.current_token and self.current_token.value in ["==", "!="]:
            eq_node = TreeNode(self.current_token.value)
            parent_node.add_child(eq_node)
            self.advance()
            self.relational(eq_node)

    def relational(self, parent_node):
        self.additive(parent_node)
        while self.current_token and self.current_token.value in ["<", ">"]:
            rel_node = TreeNode(self.current_token.value)
            parent_node.add_child(rel_node)
            self.advance()
            self.additive(rel_node)

    def additive(self, parent_node):
        self.multiplicative(parent_node)
        while self.current_token and self.current_token.value in ["+", "-"]:
            add_node = TreeNode(self.current_token.value)
            parent_node.add_child(add_node)
            self.advance()
            self.multiplicative(add_node)

    def multiplicative(self, parent_node):
        self.unary(parent_node)
        while self.current_token and self.current_token.value in ["*", "/"]:
            mul_node = TreeNode(self.current_token.value)
            parent_node.add_child(mul_node)
            self.advance()
            self.unary(mul_node)

    def unary(self, parent_node):
        if self.current_token and self.current_token.value == "!":
            unary_node = TreeNode("!")
            parent_node.add_child(unary_node)
            self.advance()
        self.primary(parent_node)

    def primary(self, parent_node):
        if self.current_token.type_id in [2, 3, 4, 5]:  # IDENTIFIER, INTEGER, FLOAT, CHARACTER
            primary_node = TreeNode(self.current_token.value)
            parent_node.add_child(primary_node)
            self.advance()
        elif self.current_token.value == "(":
            self.advance()
            expr_node = TreeNode("()")
            parent_node.add_child(expr_node)
            self.expression(expr_node)
            if self.current_token.value != ")":
                raise SyntaxError("Expected ')' after expression", self.position)
            self.advance()
        else:
            raise SyntaxError("Unexpected token", self.position)

    def print_syntax_tree(self):
        print(self.root)



if __name__ == "__main__":
    base_dir = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
    src_dir = os.path.join(base_dir, 'src')
    output_dir = os.path.join(base_dir, 'output')
    token_file = os.path.join(output_dir, 'Token.txt')

    # 读取 token 文件
    with open(token_file, 'r') as f:
        lines = f.readlines()

    # 解析 token 文件
    tokens = []
    token_pattern = re.compile(r"<(\d+), \"(.*?)\">")
    for line in lines:
        match = token_pattern.match(line.strip())
        if match:
            type_id = int(match.group(1))
            value = match.group(2)
            tokens.append(Token(type_id, value))

    # 创建解析器实例，并执行语法分析
    parser = Parser(tokens)
    parser.parse()
