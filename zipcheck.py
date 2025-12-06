# Bruce's zip file checker
import zipfile
import sys
from pathlib import Path

def zipcheck(zip_path):
    if not zip_path.endswith('.zip'):
        print("Meed your .zip file")
        return

    zip_file = Path(zip_path)
    if not zip_file.exists():
        print(f"File not found: {zip_path}")
        return

    with zipfile.ZipFile(zip_file, 'r') as z:
        file_list = z.namelist()

        # __MACOSX/ and .DS_Store are OK
        clean_files = [
            f for f in file_list
            if not (f.startswith('__MACOSX/') or f.endswith('.DS_Store'))
        ]

        # Identify items in root of zip
        top_levels = {Path(f).parts[0] for f in clean_files if '/' in f}

        if len(top_levels) == 0:
            print("All files are in the root of the ZIP file.")
        elif len(top_levels) == 1 and all(f.startswith(tuple(top_levels)) for f in clean_files):
            folder_name = list(top_levels)[0]
            print(f"OH NO! The ZIP file contains a folder named '{folder_name}'.")
            print("→ Re-zip your files so that all files are in the root, not inside a folder. Otherwise, you will get a zero!")
        else:
            print("Mixed or complex structure detected. Root files exist — likely okay - double check mannually")

        print("\nFiles inside the ZIP:")
        for f in clean_files:
            print("  -", f)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python zipcheck.py yourfile.zip")
    else:
        zipcheck(sys.argv[1])

