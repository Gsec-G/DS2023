struct StudStruct
{
	const char* name;
	//char* const name;
	double income;
};
struct Letter
{
	char a;
	char b;
};
typedef struct StudStruct Student;
void main()
{
	Student stud1 = {.name = "Popescu Maria", .income = 1000.5};
	Student stud2;
	stud2.name = "";
	stud2.income = 232;

}