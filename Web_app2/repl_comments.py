from hashlib import sha256

def create_hash(password):
    pw_bytestring = password.encode()
    return sha256(pw_bytestring).hexdigest()
password1 = input('Please enter your true password:')
hsh1 = create_hash(password1)
comments= []
while True:
	a= input('Enter your comment:')    #sometimes you have to write a string with double quotes !!
	password2 = input('Please enter another password that we can check against that:')
	hsh2 = create_hash(password2)
	if hsh1 == hsh2:
		print('Those were the same passwords')
		comments.append(a)
		print("previously entered comment:")
		x=0
		for x in comments:
			print(str(x))
       
	else:
		print('Those were different passwords')
		break