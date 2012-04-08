import sys, os

def do(_prev_version, _new_version, _prev_dir, _new_dir, _description):

    pass

if __name__ == "__main__":

    if len(sys.argv) < 6:
        print "Usage: python update_generator.py <prev_version> <new_version> <old_version_dir> <new_version_dir> <description_file>"
        sys.exit(0)

    do(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])
