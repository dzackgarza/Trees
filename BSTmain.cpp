/** Credit: David Fox **/
:
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "BSTree.h"
#include "Record.h"


using namespace std;





void Inord ( const Record& );
void Preord( const Record& );
void Postord( const Record& );

unsigned pcnt = 0;

template <class T>
void mix ( T* r, unsigned n );

const unsigned MAX_RECS = 500000;
KeyType keys[MAX_RECS];
Record least; // used in InOrderTreaversal
Record recs[MAX_RECS];
Record recs_inorder[MAX_RECS];

//used to test pre/post order traversals
Record Preorder[MAX_RECS];
Record Postorder[MAX_RECS];
unsigned ord_cnt=0;

const unsigned IND_CNT = 1050001;
unsigned ind[IND_CNT];


int main()
{

  {
    cout << "Open files"<<endl;
    ifstream inS("SR.dat", ios::in|ios::binary);
    if ( !inS )
    {
      cout << "file open error: SR.dat"<<endl;
      cout << "Make sure that this file is in the working directory"<<endl;
      cin.get();  exit(1);
    }
    ifstream inI("ind.dat", ios::in|ios::binary);
    if ( !inI )
    {
      cout << "file open error: ind.dat"<<endl;
      cout << "Make sure that this file is in the working directory"<<endl;
      cin.get();  exit(1);
    }
    ifstream in ("CISP430records.dat", ios::in|ios::binary );
    if ( !in )
    {
      cout << "file open error: CISP430records.dat"<<endl;
      cout << "Make sure that this file is in the working directory"<<endl;
      cin.get();  exit(1);
    }
    ifstream Prein ("pre.dat", ios::in|ios::binary );
    if ( !Prein )
    {
      cout << "file open error: pre.dat"<<endl;
      cout << "Make sure that this file is in the working directory"<<endl;
      cin.get();
      exit(1);
    }
    ifstream Postin ("post.dat", ios::in|ios::binary );
    if ( !Postin )
    {
      cout << "file open error: post.dat"<<endl;
      cout << "Make sure that this file is in the working directory"<<endl;
      cin.get();  exit(1);
    }
    cout << "Done: Open Files"<<endl
         <<"*************************"<<endl;

    cout << "Read Files"<<endl;


    inI.read(reinterpret_cast<char*>(ind), IND_CNT*sizeof(unsigned));
    inI.close();
    BSTree  bst;
    unsigned least_rec = 0;
    unsigned recs_read = 0;


    unsigned MAX_READ = MAX_RECS;

    MAX_READ = (MAX_READ<MAX_RECS)? MAX_READ:MAX_RECS;

    bool Final_Test = MAX_READ == MAX_RECS;
    if ( !Final_Test )
    {
      cout << "For the final test MAX_READ must be "<<MAX_RECS
           <<endl<<"*************************"<<endl;
    }

    recs[recs_read].read(in);
    keys[recs_read] = recs[recs_read].Key();
    recs_read++;
    while ( recs_read < MAX_READ)
    {
      if ( !(recs_read%((MAX_READ/10)?MAX_READ/10:1)) )
        cout << recs_read<<endl;
      Record rec;
      rec.read(in);
      if ( !in.eof() )
      {
        recs[recs_read] = rec;
        keys[recs_read] = rec.Key();
        recs_read++;
      }
    }
    in.close();


    for ( unsigned i=0; i<recs_read; i++ )
    {
      if ( !((i+recs_read)%((MAX_READ/10)?MAX_READ/10:1)) )
        cout << i+recs_read <<endl;
      Preorder[i].read(Prein);
      Postorder[i].read(Postin);
      recs_inorder[i].read(inS);
    }
    Prein.close();
    Postin.close();
    inS.close();
    cout << "Done: Read files" << endl<<"*************************"<<endl;
    cout  <<"Insert data into BSTree"<<endl;


    mix(recs,recs_read);
    mix(keys,recs_read);

    for ( unsigned i=0; i<recs_read; i++ )
    {
      bst.Insert(recs[i]);
    }
     cout << "Done: Insert" << endl
     <<"*************************"<<endl
     <<"Test: Depth"<<endl;

    unsigned bd = bst.Depth();
    const unsigned CD = 46;
    if ( Final_Test && bd != CD )
    {
      cout << "bst depth: " << bst.Depth() << endl;
      cout << "Correct Depth: " << CD<<endl
           <<"<enter> to continue"<<endl;
      cin.get();

    }
    cout << "Done: Depth"<<endl
    <<"*************************"<<endl
    <<"Test: Traversals"<<endl;
    least = recs_inorder[least_rec];
    pcnt = 0;
    bst.InOrderTraversal(Inord);
    cout << "   Done: In order traversal #1"<<endl;

    ord_cnt = 0;
    bst.PreOrderTraversal(Preord);
    cout << "   Done: Pre order traversal #1"<<endl;

    ord_cnt = 0;
    bst.PostOrderTraversal(Postord);

    cout << "   Done: Post order traversal #1"<<endl
    <<"Done: Traversals"<<endl
    <<"*************************"<<endl
    <<"Test: Find"<<endl;


    for ( unsigned i=0; i<recs_read; i++ )
    {
       Record ret = bst.Find(keys[i]);
       if ( ret.Key() != keys[i] )
       {
         cout <<i<< "  Find Error. You found the Record with key: "
         << ret.Key() <<endl<< " when searching for key: "
         << keys[i] << endl
         <<"<enter> to continue"<<endl;
         cin.get();
       }
    }
    cout << "Done: Find"<<endl
    <<"*************************"<<endl
    <<"Test: Find bad key"<<endl;


    KeyType bad_key("~badkey"); //to the right
    Record BK = bst.Find(bad_key);
    KeyType KNF("KEY NOT FOUND");
    if ( BK.Key() != KNF  )
    {
      cout << "Looking for bad Key: " << bad_key<<endl;
      cout << "  you found: " << BK << endl
      <<"<enter> to continue"<<endl;
      cin.get();
    }
    bad_key[0] = 0; //to the left
    BK = bst.Find(bad_key);
    if ( BK.Key() != KNF  )
    {
      cout << "Looking for bad Key: " << bad_key<<endl;
      cout << "  you found: " << BK << endl
      <<"<enter> to continue"<<endl;
      cin.get();
    }

    bad_key[0] = 'i'; //first letter of the first LC key
    bad_key[1] = '~'; //to the right of the LC
    BK = bst.Find(bad_key);
    if ( BK.Key() != KNF  )
    {
      cout << "Looking for bad Key: " << bad_key<<endl;
      cout << "  you found: " << BK << endl
      <<"<enter> to continue"<<endl;
      cin.get();
    }

    bad_key[0] = 'Z'; //first letter of the first RC key
    bad_key[1] = 0; //to the left of the RC
    BK = bst.Find(bad_key);
    if ( BK.Key() != KNF  )
    {
      cout << "Looking for bad Key: " << bad_key<<endl;
      cout << "  you found: " << BK << endl
      <<"<enter> to continue"<<endl;
      cin.get();
    }

    cout << "Done: Find bad key"<<endl
    <<"*************************"<<endl;

    cout<<endl<<"Call Destructor"<<endl;
  }

   cout<<endl <<"*************************"
       <<endl <<"**********done***********"
       <<endl <<"*************************"<<endl;
    return 0;
}




void Inord ( const Record& r )
{
 if ( r < least )
 {
   cout <<pcnt<< ": first: " << least.Key() << " next: "
   << r.Key() << endl
   <<"<enter> to continue"<<endl;
   cin.get();
 }
  least = r;
  pcnt++;
}

void Preord( const Record& r )
{
  if ( r != Preorder[ord_cnt++] )
  {
    cout << "Pre order traversal error:"<<endl;
    cout << "Yours: " << r << endl
         << "should be: " << Preorder[ord_cnt-1]<<endl
         <<"<enter> to continue"<<endl;
    cin.get();
  }
}

void Postord( const Record& r )
{
  if ( r != Postorder[ord_cnt++] )
  {
    cout << "Post order traversal error"<<endl;
    cout << "Yours: " << r << endl
         << "Should be: " << Preorder[ord_cnt-1]<<endl
         <<"<enter> to continue"<<endl;
    cin.get();
  }
}


template <class T>
void swap ( T* r, unsigned i, unsigned s )
{
  T temp = r[i];
  r[i] = r[s];
  r[s] = temp;
}

template <class T>
void mix ( T* r, unsigned n )
{

  static unsigned _index = 0;
  for ( unsigned i=0; i<n; i++ )
  {
    unsigned s = ind[_index++];
    swap(r,i,s);
  }
}

