import sys
import xml.etree.ElementTree as ET

stop_words = sys.stdin.readline().rstrip().split(";")
index_terms = sys.stdin.readline().rstrip().split(";")
special_tags = ["title", "abstract", "body"]

xml_tree = ""
for line in sys.stdin:
    xml_tree += line
xml_tree = "<elroot>\n" + xml_tree + "\n</elroot>"

def remove_punctuation(s):
    newS = s.replace(',', '')
    newS = newS.replace('.', '')
    newS = newS.replace('?', '')
    newS = newS.replace('!', '')
    return " ".join(newS.split())  # remove extra spaces
    
def remove_stop_words(s):
    return " ".join([word for word in s.split() if word not in stop_words])
    
def remove_short_words(s):
    return " ".join([word for word in s.split() if len(word) >= 4])
    
def print_tree(root):
    for child in root:
        print(child.text)
        print_tree(child)

def normalize(root):
    if root.text:
        root.text = root.text.lower()
        root.text = remove_punctuation(root.text)
        root.text = remove_stop_words(root.text)
        root.text = remove_short_words(root.text)
        
    for child in root:
        normalize(child)

def count_words_in_children(root):
    total = len(root.text.split()) if root.text else 0
    for child in root:
        total += count_words_in_children(child)
    return total
    
def count_words_in_special_tags(root):
    total = 0
    if root.tag in special_tags:
        return count_words_in_children(root)
    
    for child in root:
        total += count_words_in_special_tags(child)
    return total
    
def find_tag(root, tag):
    if root.tag == tag:
        return root
    for children in root:
        res = find_tag(children, tag)
        if res != False:
            return res
    return False
    
def count_occurrences(root, term):
    total = 0
    if root.text:
        for w in root.text.split():
            if w == term:
                total += 1
    for child in root:
        total += count_occurrences(child, term)
    return total

'''
useful info
root.tag = xml tag
root.text = text content
'''

# normalize tokens
root = ET.fromstring(xml_tree)
normalize(root)

title_tag = find_tag(root, "title")
abstract_tag = find_tag(root, "abstract")
body_tag = find_tag(root, "body")
L = count_words_in_children(title_tag) + \
    count_words_in_children(abstract_tag) + \
    count_words_in_children(body_tag)

densities = list()
for term in index_terms:
    title_occurrences = count_occurrences(title_tag, term)
    abstract_occurrences = count_occurrences(abstract_tag, term)
    body_occurrences = count_occurrences(body_tag, term)
    Sw = title_occurrences * 5 + abstract_occurrences * 3 + body_occurrences
    
    keyword_density = Sw / L * 100 if L != 0 else 0
    densities.append(tuple((term, keyword_density)))


densities = sorted(densities, key=lambda x: (-x[1], x[0]))
print_i = 0
while(print_i < 3 and print_i < len(densities) and densities[print_i][1] > 0):
    keyword = densities[print_i][0]
    val = densities[print_i][1]
    print(f"{keyword}: {val}")
    print_i += 1
    
    if print_i == 3:
        prev = densities[2][1]
        while print_i < len(densities) and densities[print_i][1] == prev:
            keyword = densities[print_i][0]
            val = densities[print_i][1]
            print(f"{keyword}: {val}")
            print_i += 1
            
    