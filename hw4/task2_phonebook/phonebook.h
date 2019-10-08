#ifndef TASK2_PHONEBOOK_PHONEBOOK_H
#define TASK2_PHONEBOOK_PHONEBOOK_H

struct Record;
typedef struct Record Record;

struct PhoneBook;
typedef struct PhoneBook PhoneBook;

PhoneBook* createPhoneBook();
void phoneBookAppend(char* name, char* number, PhoneBook* phonebook);
char* getName(char* number, PhoneBook* phonebook);
char* getNumber(char* name, PhoneBook* phonebook);
void destroyPhoneBook(PhoneBook* phonebook);
#endif //TASK2_PHONEBOOK_PHONEBOOK_H
