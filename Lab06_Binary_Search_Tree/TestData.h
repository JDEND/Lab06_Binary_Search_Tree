#ifndef TESTDATA_H
#define TESTDATA_H

class TestData {
public: 
	void setKey(int newKey){
	keyField = newKey;
	}

	int getKey() const{
		return keyField;
	} // Returns the key  

private:

	int keyField; // Key for the data item  
};

#endif //!TESTDATA_H