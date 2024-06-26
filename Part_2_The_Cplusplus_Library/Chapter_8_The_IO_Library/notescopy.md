# THE INPUT OUTPUT LIBRARY
    The Input Output Library provides a set of classes to perform input and output operations
    HEADERS
        1. iostream - input from and output to standard(console) input and output stream 
        2. fstream - input from and output to name files
        3. sstream - input from and output to in-memory string streams
• istream (input stream) type, which provides input operations       
• ostream (output stream) type, which provides output operations      
• cin, an istream object that reads the standard input      
• cout, an ostream object that writes to the standard output       
• cerr, an ostream object, typically used for program error messages, that writes to the standard error      
• The >> operator, which is used to read input from an istream object      
• The << operator, which is used to write output to an ostream object      
• The getline function (§ 3.2.2, p. 87), which reads a line of input from a given istream into a given string      
      
![The Input Types](../../pictures/IO_Types)

> ifstream and istringstream inherits from istream, so we can use obj of ifstream and istringstream in place of cin    

    cin << word;    ifstreamobj << word;     istringstreamobj << word
    getline(cin, line),     getline(ifstreamobj,line),      getline(istringstreamobj, line);       

> ofstream and ostringstream inherits from ostream, so we can these types in place of cout               

    cout << word;   ostreamobj << word      ostringstreamobj << word

### No Copy or Assign for IO Objects       
    ofstream out1, out2;
    out1 = out2                // error : can't assign stream objects
    ofstream print(ofstream )  // error : can't initialise the ofstream parameter type  //  function call
    out2 = print(out2)         // error : cannot copy stream objects
### No Const
    reading and writing changes the state of the subject, so const references

### Condition State
    The state of a io stream(obj) can be accessed by strm::iostate type - machine dependent integral 
![IO State](../../pictures/condition_state_ofIO.png)

### Flushing Buffer
    cout << "hi" << endl;  //  writes hi and a newline, then flushes the buffer
    cout << "hi" << flush; //  writes hi and flushes the buffer
    cout << "hi" << ends;  //  writes hi and a null, flushes the buffer
    cout << unitbuf;       //  all writes will be flushed immedietly
    cout << nounitbuf;     //  returns to normal buffering

### fstream
    along with all the operations that iostream provides, fstream adds these file specific operations
![FILE OPERATIONS](../../pictures/fstreamOperations.png)
 
