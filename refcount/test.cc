#include "rcobject.h"
#include "rcptr.h"
#include <string.h>
class String {
  public:
    String(const char* value = "");

    const char& operator[](int index) const;
    char& operator[](int index);

  private:
    struct StringValue: public RCObject {
      char *data;

      StringValue(const char* initValue);
      StringValue(const StringValue& rhs);
      void init(const char* initValue);
      ~StringValue();
    };
    RCPtr<StringValue> value;
};

void String::StringValue::init(const char* initValue) {
  data = new char[strlen(initValue) + 1];
  strcpy(data, initValue);
}

String::StringValue::StringValue(const char* initValue) {
  init(initValue);
}

String::StringValue::StringValue(const StringValue& rhs) {
  init(rhs.data);
}

String::StringValue::~StringValue() {
  delete[] data;
}

String::String(const char* initValue) : value(new StringValue(initValue)){
}

const char& String::operator[](int index) const {
  return value->data[index];
}

char& String::operator[](int index) {
  if (value->IsShared()) {
    value = new StringValue(value->data);
  }
  value->MarkUnshareable();
  return value->data[index];
}


int main()
{
  String str("data");
  String str1(str);
  String str2("world");
  str1 = str2;
}
