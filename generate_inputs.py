from argparse import ArgumentTypeError, ArgumentParser

charset = [chr(x) for x in range(ord('A'), ord('~') + 1)]

from random import randrange, choices

parser = ArgumentParser()
parser.add_argument('-s', metavar='AMOUNT', nargs='?', const=1, type=int, default=5, help="Amount of key-value pairs in storage, default = 5")
parser.add_argument('-k', metavar='KEY_LENGTH', nargs='?', const=1, type=int, default=10, help="Max size of key, default = 10")
parser.add_argument('-t', metavar='SEARCHES', nargs='?', const=1, type=int, default=20, help="Total searches to do, default = 20")
parser.add_argument('-v', metavar="SEARCHES", nargs='?', const=1, type=int, default=5, help="Valid searches to do, default = 5")
args = parser.parse_args()

def generate_single(length):
	value = ""
	for _ in range(length):
		value += choices(charset)[0]
	return value

def generate_pair():
	key = "KEY - " + generate_single(args.k)
	value = "VALUE - " + generate_single(args.k)
	return (key,value)

storage = dict()
for _ in range(args.s):
	key, value = generate_pair()
	storage[key] = value

searches = []
valid = []
keys = list(storage.keys())
for _ in range(args.t):
	if len(valid) < args.v and randrange(0,args.t) % 2 == 0:
		# remaining_valid_keys = [x for x in pairs if x[0] not in valid]
		remaining_valid_keys = keys
		valid_key = choices(remaining_valid_keys)[0]
		valid.append(valid_key)
		searches.append(valid_key)
	else:
		searches.append(generate_single(args.k))

# Output result

input_content = ""
output_content = ""

for key,value in storage.items():
	input_content += key + "\n"
	input_content += value + "\n"
input_content += "\n"
for search in searches:
	input_content += search + "\n"
	if search in storage:
		output_content += storage[search] + "\n"
	else:
		output_content += search + ": Not Found.\n"
input_content += "\n"

with open(f"./inputs/{args.s}_{args.k}_{args.t}_{args.v}.input", 'w') as f:
	f.write(input_content)
with open(f"./inputs/{args.s}_{args.k}_{args.t}_{args.v}.output", 'w') as f:
	f.write(output_content)