import tkinter as tk
from tkinter import filedialog, scrolledtext
import os
from lexical_analysis import Lexer
from Gramma_analysis import Parser
from semantic_analysis import SemanticAnalyzer
import json
import re
class Token:
    def __init__(self, type_id, value):
        self.type_id = type_id
        self.value = value

    def __repr__(self):
        return f'<{self.type_id}, "{self.value}">'

class MainApplication(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("C Language Subset Analysis")
        self.geometry("800x600")

        self.text_editor = scrolledtext.ScrolledText(self, wrap=tk.WORD, font=("Arial", 12))
        self.text_editor.pack(fill=tk.BOTH, expand=True)

        self.menu_bar = tk.Menu(self)

        self.file_menu = tk.Menu(self.menu_bar, tearoff=0)
        self.file_menu.add_command(label="Open", command=self.open_file)
        self.file_menu.add_separator()
        self.file_menu.add_command(label="Exit", command=self.quit)
        self.menu_bar.add_cascade(label="File", menu=self.file_menu)

        self.analyze_menu = tk.Menu(self.menu_bar, tearoff=0)
        self.analyze_menu.add_command(label="Lexical Analysis", command=self.perform_lexical_analysis)
        self.analyze_menu.add_command(label="Gramma Analysis", command=self.perform_gramma_analysis)
        self.analyze_menu.add_command(label="Semantic Analysis", command=self.perform_semantic_analysis)
        self.menu_bar.add_cascade(label="Analysis", menu=self.analyze_menu)

        self.config(menu=self.menu_bar)

        self.output_text = scrolledtext.ScrolledText(self, wrap=tk.WORD, font=("Arial", 12))
        self.output_text.pack(fill=tk.BOTH, expand=True)

        self.filepath = ""

    def open_file(self):
        self.filepath = filedialog.askopenfilename(filetypes=[("Text files", "*.txt")])
        if self.filepath:
            with open(self.filepath, "r") as file:
                text = file.read()
                self.text_editor.delete(1.0, tk.END)
                self.text_editor.insert(tk.END, text)

    def perform_lexical_analysis(self):
        text = self.text_editor.get(1.0, tk.END)
        category_map = self.load_category_map()
        lexer = Lexer(text, category_map)
        try:
            lexer.tokenize()
            tokens = lexer.tokens
            self.output_text.delete(1.0, tk.END)
            self.output_text.insert(tk.END, "Lexical Analysis Result:\n")
            for token in tokens:
                self.output_text.insert(tk.END, f"{token}\n")
        except LexicalError as e:
            self.output_text.delete(1.0, tk.END)
            self.output_text.insert(tk.END, f"Lexical Analysis Error: {e}\n")

    def load_category_map(self):
        base_dir = os.path.abspath(os.path.dirname(__file__))
        category_file = os.path.join(base_dir, 'word_category.json')
        with open(category_file, 'r') as file:
            category_map = json.load(file)
        return category_map

    def perform_gramma_analysis(self):
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
        parser = Parser(tokens)
        try:
            parser.parse()
            self.output_text.delete(1.0, tk.END)
            self.output_text.insert(tk.END, "Gramma Analysis Passed")
        except SyntaxError as e:
            self.output_text.delete(1.0, tk.END)
            self.output_text.insert(tk.END, f"Gramma Analysis Error: {e}")

    def perform_semantic_analysis(self):
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
        analyzer = SemanticAnalyzer(tokens)
        try:
            analyzer.analyze()
            self.output_text.delete(1.0, tk.END)
            self.output_text.insert(tk.END, "Semantic Analysis Passed\n")

            # 读取并显示中间代码
            intermediate_code_file = os.path.join(output_dir, 'intermediate_code.txt')
            with open(intermediate_code_file, 'r') as f:
                intermediate_code = f.read()
            self.output_text.insert(tk.END, "Intermediate Code:\n")
            self.output_text.insert(tk.END, intermediate_code)
        except SyntaxError as e:
            self.output_text.delete(1.0, tk.END)
            self.output_text.insert(tk.END, f"Semantic Analysis Error: {e}")


if __name__ == "__main__":
    app = MainApplication()
    app.mainloop()
