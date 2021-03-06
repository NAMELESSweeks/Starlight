import json
import sys

if len(sys.argv) != 4:
    print('Usage: ' + sys.argv[0] + ' <definitions file> <patch template> <output file>')

class Patch:
    # offset is an int
    # contents is a bytes object
    def __init__(self, offset, contents):
        self.offset = offset
        self.contents = contents

class PatchList:
    # name is a string
    # patches is an array of "Patch"es
    def __init__(self, name, patches):
        self.name = name
        self.patches = patches

# parse definitions
def_file = open(sys.argv[1], 'r')
line = def_file.readline().strip()
defs = {}
while line:
    if line.startswith('#'):
        line = def_file.readline().strip()
        continue
    defs[line.partition('=')[0].strip()] = int(line.partition('=')[2].strip(), 16)
    line = def_file.readline().strip()
print('defs: ' + str(defs))
if not 'DIST_FROM_MAIN' in defs:
    print('Could not find DIST_FROM_MAIN in definitions')
    sys.exit(1)

# parse patch template
template_file = open(sys.argv[2], 'r')
template_json = json.load(template_file)
print('template: ' + str(template_json))
if not 'build_id' in template_json:
    print('Could not find build_id in template')
    sys.exit(2)
patchlists = []
for template_key, template_value in template_json.items():
    if template_key == 'build_id':
        build_id = template_value
        continue
    if not 'name' in template_value:
        print('Could not find name in patchlist')
        sys.exit(3)
    # everything that's not build_id is treated as a patchlist
    for patchlist_key, patchlist_value in template_value.items():
        print(patchlist_value)
        patches = []
        # everything that's not name is treated as a patch
        if patchlist_key == 'name':
            continue
        if not 'type' in patchlist_value:
            print('Could not find type in patch')
            sys.exit(4)
        if not 'offset' in patchlist_value:
            print('Could not find offset in patch')
            sys.exit(5)
        if not 'contents' in patchlist_value:
            print('Could not find contents in patch')
            sys.exit(6)
        # python doesn't have switch (case), have fun sifting through the else ifs
        if patchlist_value['type'] == 'hex_le':
            # "contents": "0xDEADBEEF" or "contents": "DEADBEEF"
            # contents are little-endian
            # patches[patchlist_value['name']] = bytearray.fromhex(patchlist_value['items'].replace('0x', ''))
            try:
                patch_offset = int(patchlist_value['offset'].replace('0x', ''), 16)
            except ValueError:
                # try and get the offset from defs if it's not hex
                if not patchlist_value['offset'] in defs:
                    print('Could not find ' + str(patchlist_value['offset']) + ' in ' + sys.argv[1])
                    sys.exit(7)
                patch_offset = defs[patchlist_value['offset']]
            patches.append(Patch(patch_offset, bytearray.fromhex(patchlist_value['contents'].replace('0x', ''))))
    patchlists.append(PatchList(template_value['name'], patches))


# write ipswitch patch
with open(sys.argv[3], 'w') as pchtxt:
    pchtxt.write('// This file was automatically generated by genpatch.py\n')
    pchtxt.write('@little-endian\n')
    pchtxt.write('@nsobid-' + template_json['build_id'] + '\n')
    pchtxt.write('@flag offset_shift 0x100\n')
    for patchlist in patchlists:
        pchtxt.write('\n')
        pchtxt.write('// ' + patchlist.name + '\n')
        pchtxt.write('@enabled\n')
        for patch in patchlist.patches:
            offset_hex = hex(patch.offset).replace('0x', '').upper()
            if len(offset_hex) > 8:
                print('Offset ' + hex(patch.offset) + ' is too large!')
                sys.exit(7)
            pchtxt.write(('0' * (8 - len(offset_hex))) + offset_hex)
            pchtxt.write(' ')
            pchtxt.write(''.join('{:02X}'.format(x) for x in patch.contents))
            pchtxt.write('\n')