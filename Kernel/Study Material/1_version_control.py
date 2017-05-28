import sys 
import zipfile
import time 
import shutil 
import os
import requests
import subprocess 

BASE_VERSION = "version_0"
PREV_VERSION = "version_0"
CURR_VERSION = "version_0"

Base_version_Filename = "base.txt" 
Current_version_Filename = "curr_version.txt" 
previous_version_Filename = "pre_version.txt"
Complie_time_Filename = "compile_time.txt" 
Projet_ID_Filename = "ID.txt"
COMPARE_Filename = "compare.txt" 
PATCH_Filename = "patch.txt"
RELEASE_PATH_Filename = "release_path.txt"

##################################################################################################################################################################
#	Function :	ChangeNumValue
##################################################################################################################################################################
def ChangeNumValue (Value): 
	print "Change this Number  %c " % Value 

	if (Value == "0") : 
		print "to 1 \r\n" 
		return '1' 
	elif (Value == "1") :
		print "to 2 \r\n" 
		return '2' 
	elif (Value == "2") : 
		print "to 3 \r\n" 
		return '3' 
	elif (Value == "3") : 
		print "to 4 \r\n" 
		return '4' 
	elif (Value == "4") : 
		print "to 5 \r\n" 
		return '5' 
	elif (Value == "5") : 
		print "to 6 \r\n" 
		return '6' 
	elif (Value == "6") : 
		print "to 7 \r\n" 
		return '7' 
	elif(Value == "7") : 
		print "to 8 \r\n" 
		return '8' 
	elif (Value == "8") :
		print "to 9 \r\n" 
		return '9' 
	elif (Value == "9") : 
		print "to 0 \r\n" 
		return '0' 
			
##Mode = sys.stdin.readline()

##################################################################################################################################################################
#	Function :	Get the basic information
##################################################################################################################################################################

def fn_get_basic_info(): 

	BASE_VERSION = "version_0"
	PREV_VERSION = "version_0"
	CURR_VERSION = "version_0"

	from subprocess import Popen,PIPE 

	os.chdir("./" + arg1 + "/") 
	print("Path at terminal when executing this file\n") 
	print(os.getcwd() + "\n") 	
	
	print "Script runs in Run mode\n"
	os.system("ls")
			
	# create a base version 
	if not os.path.isfile(Base_version_Filename):
		print "Base version file is created here"
		print "Current version is base version \n"
		# Open a file
		fo = open(Base_version_Filename, "w+")
		print "Name of the file: ",fo.name
		fo.write("#define BASE_VERSION ");
		fo.write('"');		
		fo.write("%s" % BASE_VERSION);
		fo.write('"');
		fo.close();
	else:
		print "##################################"
		fo = open(Base_version_Filename, "r")		
		base_version = fo.readlines()			
		#print "",base_version[0]
		index=base_version[0].index('"')	
		BASE_VERSION = 	base_version[0][index:40];
		print "Base version = ",base_version[0][index:40]
		fo.close();


	# create a current version 
	if not os.path.isfile(Current_version_Filename):
		print "Current version file is created here"
		# Open a file
		fo = open(Current_version_Filename, "w+")
		print "Name of the file: ", fo.name
		fo.write("#define CURR_VERSION ");
		fo.write('"');		
		fo.write("%s" % CURR_VERSION);
		fo.write('"');
		fo.close();			
	else:		
		print "##################################"
		fo = open(Current_version_Filename, "r")		
		cur_version = fo.readlines()			
		#print "",cur_version[0]
		index=cur_version[0].index('"')		
		CURR_VERSION = cur_version[0][index:40];
		print "Current version = ",cur_version[0][index:40]
		fo.close();		


	# create a current version 
	if not os.path.isfile(previous_version_Filename):
		print "Current version file is created here"
		# Open a file
		fo = open(previous_version_Filename, "w+")
		print "Name of the file: ", fo.name
		fo.write("#define PREV_VERSION ");
		fo.write('"');		
		fo.write("%s" % PREV_VERSION);
		fo.write('"');
		fo.close();			
	else:		
		print "##################################"
		fo = open(previous_version_Filename, "r")		
		prev_version = fo.readlines()			
		#print "",cur_version[0]
		index=prev_version[0].index('"')		
		PREV_VERSION = prev_version[0][index:40];
		print "Previous version = ",prev_version[0][index:40]
		fo.close();		
	
	if BASE_VERSION == CURR_VERSION:
		print "Base & current versions are same"
	else:
		print "Base & current versions are not same"
		print "",BASE_VERSION
		print "",CURR_VERSION


	# create a Project ID file
	if not os.path.isfile(Projet_ID_Filename) :
		print "Project ID version file is created here"	
		# Open a file
		pid = raw_input("\n Please enter the PROJECT ID ")		
		fo = open(Projet_ID_Filename, "w+")
		print "Name of the file: ", fo.name
		fo.write("#define PROJECT_ID ");
		fo.write('"');		
		fo.write("%s" % pid);
		fo.write('"');
		fo.close();		
	else:
		print "##################################"
		fo = open(Projet_ID_Filename, "r")		
		pid = fo.readlines()			
		#print "",pid[0]
		index=pid[0].index('"')		
		print "Project ID = ",pid[0][index:40]
		fo.close();


	# create a Project compile time file
	if not os.path.isfile(Complie_time_Filename) :
		print "Project compile time file is created here"	
		# Open a file
		fo = open(Complie_time_Filename, "w+")
		print "Name of the file: ", fo.name
		fo.write("#define PROJECT_COMPILE_TIME ");
		fo.write('"');		
		fo.write("%s" % localtime);
		fo.write('"');
		fo.close();		
	else:
		print "##################################"
		fo = open(Complie_time_Filename, "r")		
		cur_time = fo.readlines()			
		#print "",pid[0]
		index=pid[0].index('"')		
		print "Complie Time = ",cur_time[0][index:70]
		fo.close();		
		
	os.chdir("../")
	print("Path at terminal when executing this file\n") 
	print(os.getcwd() + "\n") 


##################################################################################################################################################################
#	Function :	fn_release_base_version
##################################################################################################################################################################

def fn_release_base_version():
	
	ZIP_BASE_file=arg1+"_base_version"
	ZIP_file=arg1+'_last'
	ZIP_file_path=arg1+'_last'+'.zip'

	print(os.getcwd() + "\n")
	# zip the current version put in Release location & Release location
	Release_location = raw_input("\n Please Enter the Release location : ")
	
		
	shutil.make_archive(ZIP_BASE_file,'zip',arg1)		
	shutil.move(ZIP_BASE_file+'.zip',Release_location);
	
	shutil.make_archive(ZIP_file,'zip',arg1)		
	shutil.move(ZIP_file+'.zip',Release_location);
			
	os.chdir("./" + arg1 + "/") 
	print("Path at terminal when executing this file\n") 
	print(os.getcwd() + "\n")		
	
	fo = open(RELEASE_PATH_Filename, "w+")
	print "Name of the file: ", fo.name			
	fo.write("%s" % Release_location);
	fo.close();	
	
	#Change the previous version			
	fo = open(Current_version_Filename, "r")		
	cur_version = fo.readlines()			
	#print "",cur_version[0]
	index=cur_version[0].index('"')		
	CURR_VERSION = cur_version[0][index:40];
	print "Current version = ",CURR_VERSION
	fo.close();	
	
	#Update the previous version
	fo = open(previous_version_Filename, "w+")
	print "Name of the file: ", fo.name
	fo.write("#define PREV_VERSION ");				
	fo.write("%s" % CURR_VERSION);			
	fo.close();	
	
	print "Length of the string: ",len(CURR_VERSION) 
						
	if(len(CURR_VERSION) > 11): 
		print "Version number is two digit \r\n" 
		print "Value %c\n" % CURR_VERSION[10] 
		newchar = ChangeNumValue(CURR_VERSION[10]) 
		
		if( newchar >= '1' and newchar <= '9'): 
			index = 10
			updated_CURR_VERSION = CURR_VERSION[0:10] + newchar + CURR_VERSION[11:]		
		else: 
			index = 9
			char = ChangeNumValue(CURR_VERSION[9]) 				
			newchar = '0' 
			updated_CURR_VERSION = CURR_VERSION[0:9] + char + newchar +CURR_VERSION[11:]		
		print "New Current version = ",updated_CURR_VERSION
	else: 
		print "Version number is One digit \r\n"
		print "Value %c\n" % CURR_VERSION[9] 
		char = ChangeNumValue(CURR_VERSION[9]) 
		if( char >= '1' and char <= '9'): 
			index = 9
			updated_CURR_VERSION = CURR_VERSION[0:9] + char + CURR_VERSION[10:]				
		else: 
			index = 9
			char = '1' 
			newchar = '0' 				
			updated_CURR_VERSION = CURR_VERSION[0:9] + char + newchar +CURR_VERSION[10:]		
			
		print "New Current version = ",updated_CURR_VERSION
				
	#Change the current version		
	print "Current version file is created here"
	#Open a file
	fo = open(Current_version_Filename, "w+")
	print "Name of the file: ",fo.name
	fo.write("#define CURR_VERSION ");
	fo.write("%s" % updated_CURR_VERSION);
	fo.close();	
				
	os.chdir("../")
	print("Path at terminal when executing this file\n") 
	print(os.getcwd() + "\n") 
##################################################################################################################################################################
#	Function :	fn_release_base_version
##################################################################################################################################################################

def fn_release_patch():
	
	ZIP_BASE_file=arg1+"_base_version"
	ZIP_file=arg1+'_last'
	ZIP_file_path=arg1+'_last'+'.zip'
	
	os.chdir("./" + arg1 + "/") 
	print("Patch will be created\n") 
	print(os.getcwd() + "\n")	
	
	#Change the previous version			
	fo = open(Current_version_Filename, "r")		
	cur_version = fo.readlines()			
	#print "",cur_version[0]
	index=cur_version[0].index('"')		
	CURR_VERSION = cur_version[0][index:40];
	print "Current version = ",CURR_VERSION
	fo.close();	
	
	# zip the current version put in Release location & Release location
	fo = open(RELEASE_PATH_Filename, "r")
	print "Name of the file: ", fo.name		
	Release_location = fo.readlines()
	Release_location[0]=Release_location[0].rstrip('\n')
	fo.close();	
	
	os.chdir("..")
	os.chdir("./" + arg1 + "/")
	print "Release_location of the file:", Release_location[0]		
	os.chdir(Release_location[0]) 		
	print(os.getcwd() + "\n")	
	#shutil.unpack_archive(ZIP_file_path, extract_dir='tempdata')		
	
	old_release=Release_location[0]+'/'+arg1+'_last'
	
	zip1=zipfile.ZipFile(ZIP_file_path)
	zip1.extractall(old_release)
	os.chdir("..")			
	print("Path at terminal when executing this file\n") 
	print(os.getcwd() + "\n")
			
	newstr = CURR_VERSION.replace('"', "")				
	diff_file=newstr + '.diff'
	print "Name of the file path : ", old_release
	
	print ("diff -ur %s %s > %s" %( arg1,old_release,diff_file));	
	os.system("diff -ur %s %s > %s" %( arg1,old_release,diff_file));	
	
	shutil.move(diff_file,Release_location[0]);
	
	rm_path=Release_location[0]+'/'+arg1+'_last'
	shutil.rmtree(rm_path);
	rm_path=Release_location[0]+'/'+arg1+'_last'+'.zip'
	os.remove(rm_path);
	
	shutil.make_archive(ZIP_file,'zip',arg1)		
	shutil.move(ZIP_file+'.zip',Release_location[0]);
	
	os.chdir(Release_location[0]) 
	
	#Update the patch file
	fo = open(PATCH_Filename, "a+")
	print "Name of the file: ", fo.name					
	fo.write("%s" % diff_file);	
	fo.write("\n");		
	fo.close();
	os.chdir("../" + arg1 + "/")
	print("Path at terminal when executing this file\n") 
	print(os.getcwd() + "\n")	

	
	#Update the previous version
	fo = open(previous_version_Filename, "w+")
	print "Name of the file: ", fo.name
	fo.write("#define PREV_VERSION ");				
	fo.write("%s" % CURR_VERSION);			
	fo.close();	
	
	print "Length of the string: ",len(CURR_VERSION) 
						
	if(len(CURR_VERSION) > 11): 
		print "Version number is two digit \r\n" 
		print "Value %c\n" % CURR_VERSION[10] 
		newchar = ChangeNumValue(CURR_VERSION[10]) 
		
		if( newchar >= '1' and newchar <= '9'): 
			index = 10
			updated_CURR_VERSION = CURR_VERSION[0:10] + newchar + CURR_VERSION[11:]		
		else: 
			index = 9
			char = ChangeNumValue(CURR_VERSION[9]) 				
			newchar = '0' 
			updated_CURR_VERSION = CURR_VERSION[0:9] + char + newchar +CURR_VERSION[11:]		
		print "New Current version = ",updated_CURR_VERSION
	else: 
		print "Version number is One digit \r\n"
		print "Value %c\n" % CURR_VERSION[9] 
		char = ChangeNumValue(CURR_VERSION[9]) 
		if( char >= '1' and char <= '9'): 
			index = 9
			updated_CURR_VERSION = CURR_VERSION[0:9] + char + CURR_VERSION[10:]				
		else: 
			index = 9
			char = '1' 
			newchar = '0' 				
			updated_CURR_VERSION = CURR_VERSION[0:9] + char + newchar +CURR_VERSION[10:]		
			
		print "New Current version = ",updated_CURR_VERSION
			
				
	#Change the current version		
	print "Current version file is created here"
	#Open a file
	fo = open(Current_version_Filename, "w+")
	print "Name of the file: ",fo.name
	fo.write("#define CURR_VERSION ");
	fo.write("%s" % updated_CURR_VERSION);
	fo.close();	
				
	os.chdir("../")	
	print("Path at terminal when executing this file\n") 
	print(os.getcwd() + "\n")

##################################################################################################################################################################
#	Function :	fn_list_patch
##################################################################################################################################################################

def fn_list_patch():
	ZIP_BASE_file=arg1+"_base_version"
	ZIP_file=arg1+'_last'
	ZIP_file_path=arg1+'_last'+'.zip'
	
	os.chdir("./" + arg1 + "/") 
	print("Patch will be created\n") 
	print(os.getcwd() + "\n")	

	# zip the current version put in Release location 
	fo = open(RELEASE_PATH_Filename, "r")		
	Release_location = fo.readlines()
	Release_location[0]=Release_location[0].rstrip('\n')
	fo.close();	
	
	os.chdir("..")	
	print "Release_location of the file:", Release_location[0]		
	os.chdir(Release_location[0]) 		
	print(os.getcwd() + "\n")	
	
	
	fo = open(PATCH_Filename, "r")
	print "Name of the file: ", fo.name					
	line_numbers = 0
	myList = []
	for line in fo:
		myList.append(line)
		line_numbers=line_numbers+1
	
	#print(myList)	
	#print(myList[0])
	
	for index in range(line_numbers):
		print 'Current Patches :', myList[index]
	
	print "The total number of lines %d" %line_numbers


	
##################################################################################################################################################################
#	Function :	fn_Apply_patch
##################################################################################################################################################################

def fn_Apply_patch():
	BASE_folder=arg1
	ZIP_BASE_file=arg1+"_base_version"+'.zip'
	ZIP_file=arg1+'_last'
	ZIP_file_path=arg1+'_last'+'.zip'
	
	os.chdir("./" + arg1 + "/") 
	print("Patch will be created\n") 
	print(os.getcwd() + "\n")	

	# zip the current version put in Release location 
	fo = open(RELEASE_PATH_Filename, "r")		
	Release_location = fo.readlines()
	Release_location[0]=Release_location[0].rstrip('\n')
	fo.close();	
	
	os.chdir("..")	
	print "Release_location of the file:", Release_location[0]		
	os.chdir(Release_location[0]) 		
	print(os.getcwd() + "\n")
	
	fo = open(PATCH_Filename, "r")
	print "Name of the file: ", fo.name					
	line_numbers = 0
	myList = []
	for line in fo:
		myList.append(line)
		line_numbers=line_numbers+1
	
	for index in range(line_numbers):
		print 'Current Patches :', myList[index].rstrip('\n')
	
	print "The total number of lines %d" %line_numbers


	zip1=zipfile.ZipFile(ZIP_BASE_file)
	zip1.extractall(arg1)
	
	print " fn_Apply_patch !" 
	patch_index=0
	patch_name = raw_input("\n Please enter the patch name : ")
	print "\n Selected patch name %s \n" %patch_name
	
	os.chdir(BASE_folder)
	# check the patch available or not
	for index in range(line_numbers):
		if patch_name == myList[index].rstrip('\n'):
			print 'Available patch  :', myList[index]
			patch_index=index+1
			
			for new_index in range(patch_index):
				print(os.getcwd() + "\n")				
				print 'Applying patch  :', myList[new_index].rstrip('\n')
				patch_apply= "../" + myList[new_index].rstrip('\n')	
				os.system("patch -t < %s" %patch_apply);
		
	print " byeeeeeee !" 	
	
	
	
##################################################################################################################################################################
#	Function :	fn_main
##################################################################################################################################################################

def fn_main():
	from subprocess import Popen,PIPE 		
	print " Press 0  - Release the Base SW version !" 
	print " Press 1  - Release the patch !"
	print " Press 2  - See the list of patches avaiable  !"
	print " Press 3  - Apply patch on Base version  !"
	print " Press 4  - Come out  !"

	option = raw_input("\n Please select the correct option : ")
	
	if option == "0":		
		fn_release_base_version()
				
	elif option == "1":
		fn_release_patch()
	
	elif option == "2":
		fn_list_patch()		

	elif option == "3":
		fn_Apply_patch()
					
	else:	
		print "\nBye\n" 

##################################################################################################################################################################
#	end of fn
##################################################################################################################################################################

os.system('clear')
file_name =  os.path.basename(sys.argv[0])
print "\n Version Control Python Script :-  %s \n" %file_name

localtime = time.asctime( time.localtime(time.time()))
print "Local current time :", localtime
print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)

arg1 = sys.argv[1] 
	
if (len(sys.argv) > 2):
	print "This script can't handle more than one arguments"
elif (len(sys.argv) == 2): 
	if os.path.exists(arg1):
		print "Project folder exists"
		fn_get_basic_info()
		fn_main()
	else:
		print "Please pass the relevant Project folder"
		os.system('exit');
else:
	print "This script did not get any argument"
	os.system("exit");			
	
