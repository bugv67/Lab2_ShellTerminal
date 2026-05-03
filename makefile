# הגדרת הקומפיילר ודגלי הקימפול (אזהרות ודיבאג)
CC = gcc
CFLAGS = -g -Wall

# שם תוכנית היעד (הקובץ המריץ הסופי)
TARGET = myshell

# רשימת קבצי האובייקט שייווצרו מקבצי ה-C
OBJS = LineParser.o Looper.o Printers.o

# המטרה הראשית שתרוץ כשנקליד רק "make"
all: $(TARGET)

# חוק בניית התוכנית הסופית מתוך קבצי האובייקט
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# חוקי בנייה עבור כל קובץ מקור בנפרד
LineParser.o: LineParser.c LineParser.h
	$(CC) $(CFLAGS) -c LineParser.c

Looper.o: Looper.c
	$(CC) $(CFLAGS) -c Looper.c

Printers.o: Printers.c
	$(CC) $(CFLAGS) -c Printers.c

# פקודת ניקוי (make clean) למחיקת התוצרים וקימפול מחדש
clean:
	rm -f *.o $(TARGET)