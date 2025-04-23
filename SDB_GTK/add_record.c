#include "header.h"

void add_new_record(SDB **ptr,const gchar *name, float percentage) {
        SDB *newRecord = (SDB *)malloc(sizeof(SDB));
        strcpy(newRecord->name,name);
        newRecord->percentage = percentage;
       
        if (*ptr == NULL) {
            newRecord->rollno = 1;
            newRecord->next = NULL; 
            *ptr = newRecord;
        } else {
            SDB *last = *ptr;
            while (last->next != NULL) {
                last = last->next; 
            }

            newRecord->rollno = last->rollno + 1; 
            newRecord->next = NULL;
            last->next = newRecord;
        }
}
