#ifndef _VIEWDATA_H_
#define _VIEWDATA_H_

///
/// Struktura trymajaca kontakt.
///
typedef struct _contact
{
	// Nazwa kontaktu.
	std::string name;
	// Numer kontaktu.
	int number;
	// Dostepnosc kontaktu.
	bool status;
}
CONTACT;

#endif /* _VIEWDATA_H_ */