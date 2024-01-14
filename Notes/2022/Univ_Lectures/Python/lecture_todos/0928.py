import os

path = input("Enter path : ")
ext = input("Enter extension : ")
files = os.listdir(path)
txt_files = []
cnt = 0

if ext.find(".") == -1:
    ext = "." + ext

print("\n" + str(len(files)) + "files : ", end="")
for i in files:
    print(i, end=" ")
    if (len(i) > 4) and (i[-4:] == ext):
        cnt += 1
        txt_files.append(i)

print("\nSearch : " + str(cnt), end="files (")
for i in txt_files:
    print(i, end=" ")
print("\b")
if cnt > 0:
    print(")")
