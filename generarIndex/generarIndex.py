import nltk
from nltk.stem.snowball import SnowballStemmer
from collections import defaultdict
nltk.download('punkt')

num_roots = 500
num_archivos= 7
derivador = SnowballStemmer('spanish')
libros = ['libro1.txt', 'libro2.txt', 'libro3.txt','libro4.txt','libro5.txt','libro6.txt']

# Initialize a set for stopwords
stoplist = set()

# Read stop words from file into the set
with open('stoplist.txt', 'r',encoding='ISO-8859-1') as file:
    stoplist = set(file.read().split('\n'))

# Initialize defaultdict for tokens
tokens = defaultdict(set)

# Process each book
for file_id, archivo in enumerate(libros, start=1):
    with open(archivo, 'r',encoding='ISO-8859-1') as file:
        tokens_in_file = nltk.word_tokenize(file.read().lower())
        tokens_in_file = [token for token in tokens_in_file if token.isalpha()]  # filter out non-alphanumeric characters
        for token in tokens_in_file:
            root = derivador.stem(token)
            if root not in stoplist:
                tokens[root].add(file_id)

# Limit tokens to the 500 most frequent ones
tokens = dict(sorted(tokens.items(), key=lambda x: len(x[1]), reverse=True)[:num_roots])

# Sort the dictionary alphabetically
tokens = dict(sorted(tokens.items()))

# Write tokens to file
def write_file(tokens):
    with open("index.txt", 'w', encoding='ISO-8859-1') as f:
        for token, file_ids in tokens.items():
            # join the file IDs with commas to get the desired format
            f.write(f"{token}:{','.join(map(str, sorted(file_ids)))}\n")

# Call the function to write tokens to the file
write_file(tokens)
