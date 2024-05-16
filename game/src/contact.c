#include "contact.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

void AddContact(jlContact_t* contact, jlContact_t** contacts)
{
	assert(contact);

	// add element to linked list
	contact->next = *contacts;

	// set head of elements to new element
	*contacts = contact;
}

void DestroyAllContacts(jlContact_t** contacts)
{
	if (!*contacts) return;

	jlContact_t* contact = *contacts;
	while (contact)
	{
		jlContact_t* next = contact->next;
		free(contact);
		contact = next;
	}

	*contacts = NULL;
}