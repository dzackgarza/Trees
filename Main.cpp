
/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 5 - Trees
    28 October 2013

*****************************************************/

#include <iostream>
#include "Record.h"
#include "BSTree.h"
#include "MYSTRING.h"
void writestuff();
void readstuff();
void readrecords();
void printrec(const Record&);
void postcompare();

using namespace std;

void postcompare()
{
    ifstream infile_fox("pre.dat", ios::in | ios::binary);
    //ifstream infile_mine("my_post.dat", ios::in | ios::binary);
    BSTree f;
    BSTree m;
    Record r;
    cout << "Starting." << endl;
    while (infile_fox)
    {
        r.read(infile_fox);
        f.Insert(r);
    }
    infile_fox.close();
    cout << "Fox's Read." << endl;
    ifstream infile_mine("my_pre.dat", ios::in | ios::binary);
    while (infile_mine)
    {
        r.read(infile_mine);
        m.Insert(r);
    }
    cout << "Fox's Tree: " << f.Depth() <<endl;
    cout << "My tree: " << m.Depth() << endl;
}
void printrec(const Record& r)
{
    ofstream myout("my_pre.dat", ios::app | ios::binary);
    r.write(myout);
}

void readrecords()
{
    ifstream infile("CISP430records.dat", ios::in | ios::binary);
    puts("File opened");
    BSTree t;
    Record r;
    while(infile)
    {
        r.read(infile);
        t.Insert(r);
    }
    cout << "Records read." << endl;
    infile.close();

    t.PreOrderTraversal(printrec);
}

void writestuff()
{
    ofstream outfile("new_out.dat", ios::out | ios::binary);
    STRING s1("First\n");
    STRING s2("Second\n");
    STRING s3("Third\n");
    s1.write(outfile);
    s2.write(outfile);
    s3.write(outfile);
    outfile.close();
}
void readstuff()
{
    ifstream infile("new_out.dat", ios::in | ios::binary);
    STRING s1;
    STRING s2;
    STRING s3;
    puts("Strings created.");
    s1.read(infile);
    puts("String 1 read.");
    s2.read(infile);
    s3.read(infile);
    infile.close();
    cout << s1;
    cout << s2;
    cout << s3;
}
int main()
{
    puts("Test Started");
    //writestuff();
    //readstuff();
    //readrecords();
    postcompare();
    return 0;
}
