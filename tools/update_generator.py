'''
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS. If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
'''
import sys, os
import filecmp
from xml.dom.minidom import Document
from zipfile import ZipFile
import hashlib

# list that contains update rules ('type', 'path', <is directory>)
# rule types: remove (-), new (+), replace (*)
rules_list = []

common_files = [] # list of common files (files that exist in prev and new version)

def compare(_prev_dir, _new_dir, _cur_prev, _cur_new):
    '''Compare two directories and make rules
    @param _prev_dir: path to previous version directory
    @param _new_dir: path to new version directory
    @param _cur_prev: path to currently parsing directory in previous version
    @param _cur_new: path to currently parsing directory in new version
    '''

    global rules_list
    global common_files
    
    comp = filecmp.dircmp(_cur_prev, _cur_new)

    # paths that exist only in previous version, must to be deleted
    for path in comp.left_only:
        _path = os.path.join(_cur_prev, path)
        rel_path = os.path.relpath(_path, _prev_dir)
        rules_list.append(('-', rel_path, os.path.isdir(_path)))

    # path that exist just in new version, must to be copied
    for path in comp.right_only:
        _path = os.path.join(_cur_new, path)
        rel_path = os.path.relpath(_path, _new_dir)
        rules_list.append(('+', rel_path, os.path.isdir(_path)))

    # compare files
    for path in comp.diff_files:
        _path = os.path.join(_cur_new, path)
        rel_path = os.path.relpath(_path, _new_dir)
        rules_list.append(('*', rel_path, os.path.isdir(_path)))

    # call compare recursively, for common directories
    for path in comp.common_dirs:
        compare(_prev_dir, _new_dir, os.path.join(_cur_prev, path), os.path.join(_cur_new, path))

def collectFiles(_dir, _new_dir):
    """Recursively find files in \p _dir and return list of them.
    @param _dir: Path to directory for files searching
    @param _new_dir: Path to new version directory (need to calculate relative path)
    @return Return list with relative path to founded files
    """
    result = []
    for root, dirs, files in os.walk(os.path.join(_new_dir, _dir)):
        for f in files:
            path = os.path.join(root, f)
            result.append(os.path.relpath(path, _new_dir))

    return result

def do(_prev_version, _new_version, _prev_dir, _new_dir, _description, _output_file):
    """Makes update file
    @param _prev_version: Name of previous version
    @param _new_version: Name of new version
    @param _prev_dir: Path to previous version directory
    @param _new_dir: Path to new version directory
    @param _description: Path to description file
    @param _output_file: Path to generated update file
    """

    # iterate all directories fill rules
    print "Analyze trees..."
    compare(_prev_dir, _new_dir, _prev_dir, _new_dir)

    print "Rules: "
    for rule in rules_list:
        tp, path, is_dir = rule
        print "[%s] %s <- %s" % (tp, path, str(is_dir))

    # create _info.xml
    print "Create _info.xml file..."
    doc = Document()
    root = doc.createElement("info")
    doc.appendChild(root)

    version = doc.createElement("version")
    prev_ver = doc.createElement("prev")
    prev_ver_value = doc.createTextNode(_prev_version)
    prev_ver.appendChild(prev_ver_value)
    new_ver = doc.createElement("new")
    new_ver_value = doc.createTextNode(_new_version)
    new_ver.appendChild(new_ver_value)

    version.appendChild(prev_ver)
    version.appendChild(new_ver)

    rules = doc.createElement("rules")

    root.appendChild(version)
    root.appendChild(rules)

    # write rules into xml
    for r in rules_list:
        tp, path, is_dir = r
        rule = doc.createElement("rule")
        rule.setAttribute("type", tp)

        is_dir_value = 0
        if is_dir:
            is_dir_value = 1
        rule.setAttribute("is_dir", str(is_dir_value))
        
        rule_path = doc.createTextNode(path)
        rule.appendChild(rule_path)

        rules.appendChild(rule)

    info_xml = doc.toprettyxml()

    # create archive
    print "Pack update file..."
    zip_file = ZipFile(_output_file, 'w')
    zip_file.writestr('_info.xml', info_xml)

    for rule in rules_list:
        tp, path, is_dir = rule

        if tp == '-':
            continue

        files = []
        if is_dir:
            files.extend(collectFiles(path, _new_dir))
        else:
            files.append(path)

        for f in files:
            print 'append %s into update' % f
            zip_file.write(os.path.join(_new_dir, f), "files/" + f)

    if os.path.exists(_description):
        zip_file.write(_description, 'description.html')
    
    zip_file.close()

    sz = os.path.getsize(_output_file)
    md5 = hashlib.md5()
    f = open(_output_file, 'r')
    md5.update(f.read())
    f.close()

    print "Update size: %u bytes" % sz
    print "md5: %s" % str(md5.hexdigest())

    # make checksum file
    f = open(_output_file + ".checksum", 'w')
    f.write("size: %u\n" % sz)
    f.write("md5: %s" % str(md5.hexdigest()))
    f.close()
    

if __name__ == "__main__":

    if len(sys.argv) < 7:
        print "Usage: python update_generator.py <prev_version> <new_version> <old_version_dir> <new_version_dir> <description_file> <output file>"
        sys.exit(0)

    do(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6])
