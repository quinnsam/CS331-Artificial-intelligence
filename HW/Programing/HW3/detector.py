#!/usr/bin/env python
# -*- coding: utf-8 -*-
################################################################################
#         ____ ____    __________ _                                            #
#        / ___/ ___|  |___ /___ // |                                           #
#       | |   \___ \    |_ \ |_ \| |                                           #
#       | |___ ___) |  ___) |__) | |                                           #
#        \____|____/  |____/____/|_|                                           #
#        _   ___        __    _  _     _____                                   #
#       | | | \ \      / /  _| || |_  |___ /                                   #
#       | |_| |\ \ /\ / /  |_  ..  _|   |_ \                                   #
#       |  _  | \ V  V /   |_      _|  ___) |                                  #
#       |_| |_|  \_/\_/      |_||_|   |____/                                   #
################################################################################
# Imports
import getopt
import sys
import os
import string
import ast


#global varibles
i = []
t = []
bag = []
vocab = []

def usage():
    print sys.argv[0] + "  <it>||<input,train> [hv] [help]"
    print "\t-i,--input\t\tInput file"
    print "\t-t,--train\t\tTraining file"
    print "\t-v\t\t\tVerbose output"
    print "\t-vv\t\t\tVery Verbose output"
    print "\t-h,--help\t\tPrint usage message"

def data_print(l):
    for tup in l:
        print str(tup[1]) + "\t" + tup[0]

def output(out_file, l, verbose):
    if verbose:
        print "Output file: " + out_file


def preprocess(input_file, train_file, verbose):
    global i
    global t
    global bag
    global vocab
    if verbose:
        print "Input file: " + str(input_file)
        print "Train file: " + str(train_file)

    # Sanitize input files
    with open(input_file) as f:
        for line in f:
            #print '##### ' + line.strip() + '######'
            temp = line.split(',')
            if len(temp) == 2:
                i.append(((temp[0].translate(None, string.punctuation)).lower(),bool(int(temp[1].strip(temp[1].translate(None, string.digits))))))

    with open(train_file) as f:
        for line in f:
            #print '##### ' + line.strip() + '######'
            temp = line.split(',')
            if len(temp) == 2:
                t.append(((temp[0].translate(None, string.punctuation)).lower(),bool(int(temp[1].strip(temp[1].translate(None, string.digits))))))

    if verbose > 1:
        print 'Test data:'
        data_print(i)
        print 'Train data:'
        data_print(t)

    for tup in i:
        for word in tup[0].split(' '):
            if word:
                bag.append(word.lower())

    for tup in t:
        for word in tup[0].split(' '):
            if word:
                vocab.append(word.lower())

    vocab = sorted(vocab)

    # Write to files
    pre_train = open('preprocessed_train.txt', 'wb')
    pre_test  = open('preprocessed_test.txt', 'wb')

    print ', '.join(sorted(vocab)) + ', classlablel'
    pre_train.write(', '.join(vocab) + ', classlabel\n')
    for tup in t:
        tl = sorted(tup[0].split(' '))
        if '' in tl: tl.remove('')
        #print ', '.join(tl)
        for word in vocab:
            if word in tl:
                print'1,',
                pre_train.write('1,')
            else:
                print '0,',
                pre_train.write('0,')
        print tup[1]
        pre_train.write(str(tup[1]) + '\n')

    pre_test.write(', '.join(vocab) + ', classlabel\n')
    for tup in i:
        tl = sorted(tup[0].split(' '))
        if '' in tl: tl.remove('')
        #print ', '.join(tl)
        for word in vocab:
            if word in tl:
                print'1,',
                pre_test.write('1,')
            else:
                print '0,',
                pre_test.write('0,')
        print tup[1]
        pre_test.write(str(tup[1]) + '\n')



    bag = sorted(bag)
    vocab = sorted(vocab)

    pre_train.close()
    pre_test.close()





def classification(verbose):
    if verbose:
        print "Bag of words: ", bag
        print "vocab: ", vocab


def main():

    # Get all command line arguments
    try:
        opts, args = getopt.getopt(sys.argv[1:], "i:t:vh", ["help", "input=", "train="])
    except getopt.GetoptError as err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)



    input_file = 'test_text.txt'
    train_file = 'training_text.txt'
    verbose = 0
    for o, a in opts:
        if o == "-v":
            verbose = verbose + 1
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ("-i", "--input"):
            input_file = a
        elif o in ("-t", "--train"):
            train_file = a
        else:
            assert False, "unhandled option"
            usage()
            sys.exit(2)

    # Check if all required arguments are provided
    if input_file == None or train_file == None:
        usage()
        sys.exit(3)

    # Check if all data files are present on the host
    if os.path.isfile(input_file) and os.path.isfile(train_file):
        # Preprocess the data from the files provided
        preprocess(input_file, train_file, verbose)
        # Classify the normalized data
        classification(verbose)
    else:
        print "One or more of the files provided are not present"
        sys.exit(4)


if __name__ == "__main__":
        main()
