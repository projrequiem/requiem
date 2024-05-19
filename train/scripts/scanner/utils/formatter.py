
def insertTabs(count):
    output = ['\t' for i in range(count)]
    return ''.join(output)
def remove_nest(string):
    output = ''
    nest = 0
    index = 0
    for i in range(len(string)):
        if string[i] == '{':
            nest += 1
        elif string[i] == '}':
            nest -= 1
            output += ';'
            continue
        elif nest == 0:
            output += string[i]
    return output
def remove_comment_block(string):
    output = ""
    q = []
    q += string.split("/*")
    while len(q) > 0:
        substring = q.pop(0)
        blocks = substring.split("*/")
        if len(blocks) == 1:
            output += blocks[0]
        else:
            output += blocks[1]
    return output
def remove_comments(string):
    output = ''
    count = 0
    buf = ''
    for i in range(len(string)):
        c = string[i]
        if count == 0:
            if c == '/':
                count += 1
                buf += c
            else:
                buf += c
                output += buf
                buf = ''
        elif count == 1:
            if c == '/':
                count += 1
                buf = ''
            else:
                count = 0
                buf += c
                output += buf
                buf = ''
        elif count == 2:
            if c == '\n':
                output += c
                count = 0
    return output
def remove_func(string):
    output = []
    q = []
    q += string.split(";")
    while len(q) > 0:
        substring = q.pop(0).strip()
        if "(" in substring:
            continue
        if len(substring) > 1:
            output.append(substring+";")
    return "\n".join(output)

def remove_ass(string):
    output = []
    q = []
    q += string.split(";")
    while len(q) > 0:
        substring = q.pop(0).strip()
        if "=" in substring:
            output.append(substring.split("=")[0] + ";")
        elif len(substring) > 1:
            output.append(substring+";")
    return "\n".join(output)