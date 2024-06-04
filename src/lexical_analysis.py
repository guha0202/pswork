import re
import json
import os

# Token 类，用于表示词法单元
class Token:
    def __init__(self, type_id, value):
        self.type_id = type_id
        self.value = value

    def __repr__(self):
        return f'<{self.type_id}, "{self.value}">'

# 自定义异常类，用于词法分析错误
class LexicalError(Exception):
    def __init__(self, message, position):
        self.message = message
        self.position = position

    def __str__(self):
        return f"LexicalError: {self.message} at position {self.position}"

# Lexer 类，执行词法分析
class Lexer:
    def __init__(self, source_code, category_map):
        self.source_code = source_code
        self.tokens = []
        self.category_map = category_map
        self.token_specification = [
            ('KEYWORD', r'\b(main|float|char|int|return|if|else|while)\b'),  # Keywords
            ('FLOAT', r'\d+\.\d+'),                                         # Float literals
            ('INTEGER', r'\d+'),                                            # Integer literals
            ('IDENTIFIER', r'[a-zA-Z_]\w*'),                                # Identifiers
            ('CHARACTER', r'\'[^\']*\''),                                   # Character literals
            ('LOGICAL_OP', r'&&|\|\|'),                                     # Logical operators (excluding !)
            ('OPERATOR', r'!=|==|[+\-*/=><]'),                              # Arithmetic and comparison operators (including != and ==)
            ('LOGICAL_NOT', r'!'),                                          # Logical NOT operator
            ('DELIMITER', r'[(){},;]'),                                     # Delimiters
            ('SKIP', r'[ \t\n]+'),                                          # Skip whitespace and newline
            ('MISMATCH', r'.'),                                             # Any other character
        ]
        self.token_regex = re.compile('|'.join(f'(?P<{pair[0]}>{pair[1]})' for pair in self.token_specification))

    # 执行词法分析
    def tokenize(self):
        try:
            for match in self.token_regex.finditer(self.source_code):
                kind = match.lastgroup
                value = match.group(kind)
                if kind == 'SKIP':
                    continue
                elif kind == 'MISMATCH':
                    raise LexicalError(f'Unexpected character {value}', match.start())
                elif kind == 'KEYWORD':
                    type_id = self.category_map['KEYWORD']
                elif kind == 'IDENTIFIER':
                    type_id = self.category_map['IDENTIFIER']
                elif kind == 'INTEGER':
                    type_id = self.category_map['INTEGER']
                elif kind == 'FLOAT':
                    type_id = self.category_map['FLOAT']
                elif kind == 'CHARACTER':
                    type_id = self.category_map['CHARACTER']
                elif kind == 'LOGICAL_OP':
                    type_id = self.category_map['LOGICAL_OP']
                elif kind == 'OPERATOR':
                    type_id = self.category_map['OPERATOR']
                elif kind == 'LOGICAL_NOT':
                    type_id = self.category_map['LOGICAL_OP']  # Logical NOT is considered a logical operator
                elif kind == 'DELIMITER':
                    type_id = self.category_map['DELIMITER']
                self.tokens.append(Token(type_id, value))
        except Exception as e:
            # 抛出自定义的词法错误
            raise LexicalError(str(e), match.start())

# 主函数，读取输入文件，执行词法分析，并将结果写入输出文件
if __name__ == "__main__":
    # 获取当前脚本所在的目录的父目录
    base_dir = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
    src_dir = os.path.join(base_dir, 'src')
    output_dir = os.path.join(base_dir, 'output')
    category_file = os.path.join(src_dir, 'word_category.json')
    input_file = os.path.join(src_dir, 'example.txt')
    output_file = os.path.join(output_dir, 'token.txt')

    # 读取词法单元分类映射
    with open(category_file, 'r') as f:
        category_map = json.load(f)

    # 读取输入文件内容
    with open(input_file, 'r') as f:
        source_code = f.read()
    # 创建词法分析器实例，并执行词法分析
    lexer = Lexer(source_code, category_map)
    try:
        lexer.tokenize()
    except LexicalError as e:
        print(e)
        exit(1)

    # 确保输出目录存在
    os.makedirs(output_dir, exist_ok=True)

    # 将词法分析结果写入输出文件
    with open(output_file, 'w') as f:
        for token in lexer.tokens:
            f.write(f"{token}\n")
