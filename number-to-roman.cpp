#include <iostream>

using namespace std;

class ElementsList;

class Element {
        
    private:
        Element *mpNext;     

    public:
        Element() {mpNext = NULL;}
        virtual ~Element() {}
        virtual void print() = 0;
        virtual char myLetter() = 0;
        virtual int myValue() = 0;
        friend class ElementsList;
        friend ostream& operator<<(ostream &os, const ElementsList& list);

};

class ElementsList {
    private:
        Element *mpHead;

    public:
        ElementsList():mpHead(NULL){}
        ~ElementsList();
        bool AddElement(Element *pElement);
        int find(char letter);
        int RomantoNumber(string s);
        friend ostream& operator<<(ostream &os, const ElementsList& list);
};


ElementsList::~ElementsList() {
    Element *pCurrent, *pNext;

    for (pCurrent = mpHead; pCurrent != NULL; pCurrent = pNext) {
        pNext = pCurrent->mpNext;
        delete pCurrent;
    }
}

bool ElementsList::AddElement(Element *pElement) {

    if (!mpHead) {
        mpHead = pElement;
        return true;
    }

    Element *pCurrent, *pPrevious;

    for (pCurrent = mpHead; pCurrent != NULL; pCurrent=pCurrent->mpNext ) {
        pPrevious = pCurrent;
    } 

    pPrevious->mpNext = pElement;
    return true;
}

int ElementsList::find(char letter) {

	Element *pCurrent;

    for (pCurrent = mpHead; pCurrent != NULL; pCurrent=pCurrent->mpNext ) {
        if(pCurrent->myLetter()==letter) {
        	return pCurrent->myValue();
        } 
    } 

	return -1;
}

int ElementsList::RomantoNumber(string s) {

    int resp = 0, temp;

    for (int i = 0; i < s.size() - 1; ++i)
    {
    	temp = find(s[i]);

        if (temp < find(s[i+1]))
            resp -= temp;
        else
            resp += temp;
    }
    resp += find(s[s.size()-1]);

    cout<<resp<<endl;
}


ostream& operator<<(ostream &os, const ElementsList& list) {

    Element *pCurrent;

    for (pCurrent = list.mpHead ; pCurrent != NULL; pCurrent = pCurrent->mpNext) {
        pCurrent->print();
    }

    return os;

}

class MajorRoman : public Element {
    private:
        char letter;
        int value;

    public:
    MajorRoman(char lt, int val):letter(lt), value(val){}
    ~MajorRoman() {}
    int myValue() { return value; }
    char myLetter() { return letter; }
    void print() { cout<<letter<<" "<<value<<endl; } 
};


class MinorRoman : public Element {
    private:
        char letter;
        int value;

    public:
    MinorRoman(char lt, int val):letter(lt), value(val){}
    ~MinorRoman() {}
    int myValue() { return value; }
    char myLetter() { return letter; }
    void print() { cout<<letter<<" "<<value<<endl; } 
};
 
int main() {
    ElementsList list;
    Element *p;

    p = new MinorRoman('I', 1);
    list.AddElement(p);
    p = new MinorRoman('V', 5);
    list.AddElement(p);
    p = new MinorRoman('X', 10);
    list.AddElement(p);
    p = new MinorRoman('L', 50);
    list.AddElement(p);

    p = new MajorRoman('C', 100);
    list.AddElement(p);
    p = new MajorRoman('D', 500);
    list.AddElement(p);
    p = new MajorRoman('M', 1000);
    list.AddElement(p);

    cout<<list;

    string s;
    cout<<"Ingrese un numero romano: ";
    cin>>s;

    list.RomantoNumber(s);

    return 0;
}