#!/usr/bin/bash -e

#You must set these variables before you run this script
###########################################################
test_file=moby10b.txt #input file you are testing
test_output_file=test1.txt #this is the name of the output file of all the cat files together

##############################
#setting chunk arguments here#
##############################
test_suffix1=37 #first test_suffix you may want to test
test_suffix2=gw #second test suffix you may want to test
test_prefix=part-- #prefix you set
test_prefix_del=$test_prefix* 
test_char_count=100000
test_word_count=20000
test_line_count=1000

###################################
# booleans to set addition options#
###################################
test_files=1 #turn to 1 to print out file names to check prefix and suffix
test_cat=0 #turn to 1 to print original file
test_cat_char=0 #turn to 1 to print out char output files
test_cat_word=0 #turn to 1 to print out word output files
test_cat_line=0 #turn to 1 to print out line output files
test_output_del=$test_output_file*
test_error=1 # turn to 1 to test potential errors which are located at the bottom.

cat_chunk_files() {
    echo -e "\n----------------------------------------"
    echo -e "This is the cat of the files altogether"
    echo "------------------------------------------"
    cat $test_prefix_del
    echo "------------------------------------------"
}

create_output_cat() {
    cat $test_prefix_del > $test_output_file
    echo -n "This is WC of $test_file:  "
    wc < $test_file
    echo -n "This is WC of $test_output_file:  "
    wc < $test_output_file
}

compare_file() {
    result=$(diff $test_file $test_output_file)
    if [ $? -eq 0 ] ; then
        echo "files are the same"
    else
        echo -n "files are different: "
        echo "$result"
    fi
}

correct_file_count_char() {
    total_char=$(wc -c < $test_file)
    echo $(( $total_char % $test_char_count ? $total_char / $test_char_count+1 : $total_char / $test_char_count ))
}

correct_file_count_word() {
    total_word=$(wc -w < $test_file)
    echo $(( $total_word % $test_word_count ? $total_word / $test_word_count + 1 : $total_word / $test_word_count ))
}

correct_file_count_line() {
    total_line=$(wc -l < $test_file)
    echo $(( $total_line % $test_line_count ? $total_line / $test_line_count + 1 : $total_line / $test_line_count ))
}

echo -e "\n#################################"
echo -e "#################################"
echo -e "##### TESTER FOR PROJECT 2 ######"
echo -e "#################################"
echo -e "\nTEST INPUT FILE: $test_file"
echo "TEST OUTPUT FILE: $test_output_file"
echo "PREFIX: $test_prefix"
echo "SUFFIX 1: $test_suffix1"
echo -e "SUFFIX 2: $test_suffix2\n"
if [[ ${test_cat} -eq 1 ]] ; then
    echo -e "This is the cat file of the original file"
    echo "---------------------------------------------"
    more $test_file
    echo -e "---------------------------------------------\n"
fi

echo -e "------------------------"
echo -e ":TEST CHARACTER COUNT:"
echo -e "------------------------"
echo -n "Total characters: " ; wc -c < $test_file
chunk -f $test_file -c $test_char_count -p $test_prefix -s $test_suffix1
echo -n "Total files by -c $test_char_count: " ; ls $test_prefix_del | wc -l
echo -n "Correct number of files for chunk: "
correct_file_count_char
create_output_cat
if [[ $test_cat_char -eq 1 ]] ; then
    cat_chunk_files
fi

if [[ $test_files -eq 1 ]] ; then
    echo -e "Files Name"
    ls $test_prefix_del
fi
echo -n "Character file check: "
compare_file
rm $test_prefix_del
rm $test_output_file

echo -e "\n-------------------"
echo -e ":TEST WORD COUNT:"
echo -e "-------------------"
echo -n "Total words: " ; wc -w < $test_file
echo -n "Total files by -w $test_word_count: "
chunk -f $test_file -w $test_word_count -p $test_prefix -s $test_suffix2
ls $test_prefix_del | wc -l
echo -n "Correct number of files for chunk: "
correct_file_count_word
create_output_cat
if [[ $test_cat_word -eq 1 ]] ; then
    cat_chunk_files
fi

if [[ $test_files -eq 1 ]] ; then
    echo -e "Files Name"
    ls $test_prefix_del
fi
echo -n "Word file check: "
compare_file
rm $test_prefix_del
rm $test_output_file

echo -e "\n-------------------"
echo -e ":TEST LINE COUNT:"
echo -e "-------------------"
echo -n "Total lines: " ; wc -l < $test_file
echo -n "Files creates by -l $test_line_count: "
chunk -f $test_file -l $test_line_count -p $test_prefix
ls $test_prefix_del | wc -l
echo -n "Correct number of files for chunk: "
correct_file_count_line
create_output_cat
if [[ $test_cat_line -eq 1 ]] ; then 
    cat_chunk_files
fi

if [[ $test_files -eq 1 ]] ; then
    echo -e "Files Name"
    ls $test_prefix_del
fi
echo -n "Line file check: "
compare_file
rm $test_output_file

echo -e "\n-------------------------"
echo -e "ERROR CHECK: EXISTING FILE"
echo -e "----------------------------"
echo -e "we reached an error due to trying to recreate a file thats already existing"
chunk -f $test_file -w 1 -p $test_prefix || true
rm $test_prefix_del
echo -e "\n-----------------------------"
echo -e "TEST STDREDIRECT & DEFAULT"
echo -e "------------------------------"
chunk < $test_file
echo -e "Default file name:"
ls x*
echo -n "this is how many files are created using the default values: "
ls x* | wc -l
rm x*

if [[ $test_error -eq 1 ]] ; then
    echo -e "\nERROR CHECK"
    chunk -f $test_file -l -p $test_prefix || true
    chunk -f $test_file -l 1 -w 2 || true
    chunk -f $test_file -c 2 -l 4 || true
    chunk -f $test_file -l 0 || true
    chunk -f $test_file -w 0 || true
    chunk -f $test_file -c 0 || true
    chunk || true
    chunk -f $test_file -s aff || true
    chunk -f $test_file -s a0 || true
    chunk -f $test_file || true
    rm x*
fi

