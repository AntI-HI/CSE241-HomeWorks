JFLAGS = -g
JC = javac
.SUFFIXES: .java .class

	
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
    MyCollection.java \
    MyIterator.java \
    MySet.java \
    MyList.java \
    MyQueue.java \
    MyHashSet.java \
    MyArrayList.java \
    MyLinkedList.java \
    Main.java \

default: classes

run: classes
	java Main

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class