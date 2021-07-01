//file: animal.h
//Purpose: Declaration of the Animal class

class Animal
{
public:
  Animal();
  Animal(string mkind,int mage,bool mtaste);

  string getKind();
  int getAge();
  bool getTaste();

private:
  string kind;
  int age;
  bool taste;//carnivore or herbivore

};
