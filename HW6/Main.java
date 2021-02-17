public class Main {

    public static void main(String[] args) {
        
        System.out.println("\n\n-------------------------------------------------------------");
        System.out.println("-------------------------------------------------------------");
        System.out.println("Containers with Integer type Tests.");
        System.out.println("-------------------------------------------------------------");
        System.out.println("-------------------------------------------------------------\n\n");

        MyLinkedList<Integer> ll1 = new MyLinkedList<Integer>();
        MyLinkedList<Integer> ll2 = new MyLinkedList<Integer>();

        for (int i =0; i < 15; ++i)
            ll2.add(i);

        for (int i =0; i < 5; ++i)
            ll1.add(i+1);

        System.out.println(ll1.contains(6));

        System.out.println(ll2.containsAll(ll1));

        ll2.addAll(ll1);

        System.out.println(ll2.toString());

        ll2.removeAll(ll1);

        System.out.println(ll2.toString());

        for (int nums: ll1) {
            System.out.print(nums + " ");
        }
        System.out.println();

        MyIterator<Integer> itr = ll1.iterator();
        try {
            itr.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }
        
        try {
            itr.next();
            itr.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }
        System.out.println("iterate through");
        while(itr.hasNext()) {
            System.out.print(itr.next() + " ");
        }


        System.out.println("\n" + ll1.poll());
        System.out.println(ll1.toString());
        ll1.offer(0);
        System.out.println(ll1.toString());
        System.out.println(ll1.element());

        // MyArrayList TEST
        MyArrayList<Integer> AL1 = new MyArrayList<>();
        MyArrayList<Integer> AL2 = new MyArrayList<>();

        for (int i =0; i < 5; ++i)
            AL1.add(i+1);

        for (int i =0; i < 15; ++i)
            AL2.add(i+1);

        System.out.println(AL1.toString());
        System.out.println(AL2.toString());

        System.out.println(AL1.contains(5));

        System.out.println(AL2.containsAll(ll2));
        System.out.println(ll2.toString());
        ll2.poll();
        System.out.println(ll2.toString());
        System.out.println(AL2.toString());
        System.out.println(AL2.containsAll(ll2));

        AL2.addAll(ll1);

        System.out.println(AL2.toString());
        System.out.println(AL1.toString());
        AL2.removeAll(AL1);

        System.out.println(AL2.toString());

        for (int nums: AL1) {
            System.out.print(nums + " ");
        }
        System.out.println();

        MyIterator<Integer> itr2 = AL1.iterator();
        try {
            itr2.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        try {
            itr2.next();
            itr2.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        while(itr2.hasNext()) {
            System.out.print(itr2.next() + " ");
        }

        // MyHashSet TEST
        System.out.println("\n----------------------------------------------");
        System.out.println("MyHashSet TEST");
        System.out.println("----------------------------------------------");
        MyHashSet<Integer> HS1 = new MyHashSet<>();
        MyHashSet<Integer> HS2 = new MyHashSet<>();

        for (int i =0; i < 5; ++i)
            HS1.add(i+1);

        for (int i =0; i < 15; ++i)
            HS2.add(i+1);

        // Let's try to add duplicate elements to the Hash Set.
        HS1.add(5);
        HS2.add(15);

        System.out.println(HS1.toString());
        System.out.println(HS2.toString());

        System.out.println(HS1.contains(5));

        System.out.println(HS2.containsAll(ll2));
        System.out.println(ll2.toString());
        ll2.poll();
        System.out.println(ll2.toString());
        System.out.println(HS2.toString());
        System.out.println(HS2.containsAll(ll2));

        HS2.addAll(ll1);

        System.out.println(HS2.toString());
        System.out.println(HS1.toString());
        HS2.removeAll(HS1);

        System.out.println(HS2.toString());

        for (int nums: HS1) {
            System.out.print(nums + " ");
        }
        System.out.println();

        MyIterator<Integer> itr3 = HS1.iterator();
        try {
            itr3.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        try {
            itr3.next();
            itr3.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        while(itr3.hasNext()) {
            System.out.print(itr3.next() + " ");
        }
        System.out.println();

        System.out.println(HS1.toString());
        System.out.println(ll1.toString());
        HS1.retainAll(ll1);
        System.out.println(HS1.toString());

        ll1.clear();
        ll2.clear();

        System.out.println(ll1.toString());

        //Containers with String type Tests.
        System.out.println("\n\n-------------------------------------------------------------");
        System.out.println("-------------------------------------------------------------");
        System.out.println("Containers with String type Tests.");
        System.out.println("-------------------------------------------------------------");
        System.out.println("-------------------------------------------------------------\n\n");



        MyLinkedList<String> ll3 = new MyLinkedList<String>();
        MyLinkedList<String> ll4 = new MyLinkedList<String>();

        for (int i =0; i < 15; ++i)
            ll4.add("A" +i);

        for (int i =0; i < 5; ++i)
            ll3.add("A" + i);

        System.out.println(ll3.contains("B"));

        System.out.println(ll4.containsAll(ll4));

        ll4.addAll(ll3);

        System.out.println(ll4.toString());

        ll4.removeAll(ll3);

        System.out.println(ll4.toString());

        for (String nums: ll3) {
            System.out.print(nums + " ");
        }
        System.out.println();

        MyIterator<String> itr4 = ll3.iterator();
        try {
            itr4.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        try {
            itr4.next();
            itr4.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        while(itr4.hasNext()) {
            System.out.print(itr4.next() + " ");
        }
        
        System.out.println('\n' + ll3.toString());

        System.out.println("\n" + ll3.poll());
        System.out.println(ll3.toString());
        ll3.offer("C");
        System.out.println(ll3.toString());
        System.out.println(ll3.element());

        // MyArrayList TEST
        MyArrayList<String> AL3 = new MyArrayList<String>();
        MyArrayList<String> AL4 = new MyArrayList<String>();

        for (int i =0; i < 5; ++i)
            AL3.add("A" +i);;

        for (int i =0; i < 15; ++i)
            AL4.add("A" +i);;

        System.out.println(AL3.toString());
        System.out.println(AL4.toString());

        System.out.println(AL3.contains("C"));

        System.out.println(AL4.containsAll(ll4));
        System.out.println(ll4.toString());
        ll4.poll();
        System.out.println(ll4.toString());
        System.out.println(AL4.toString());
        System.out.println(AL4.containsAll(ll4));

        AL4.addAll(ll3);

        System.out.println(AL4.toString());
        System.out.println(AL3.toString());
        AL4.removeAll(AL3);

        System.out.println(AL4.toString());

        for (String nums: AL3) {
            System.out.print(nums + " ");
        }
        System.out.println();

        MyIterator<String> itr5 = AL3.iterator();
        try {
            itr5.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        try {
            itr5.next();
            itr5.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        while(itr5.hasNext()) {
            System.out.print(itr5.next() + " ");
        }

        // MyHashSet TEST
        System.out.println("\n----------------------------------------------");
        System.out.println("MyHashSet TEST");
        System.out.println("----------------------------------------------");
        MyHashSet<String> HS3 = new MyHashSet<String>();
        MyHashSet<String> HS4 = new MyHashSet<String>();

        for (int i =0; i < 5; ++i)
            HS3.add("A" +i);;

        for (int i =0; i < 15; ++i)
            HS4.add("A" +i);;

        // Let's try to add duplicate elements to the Hash Set.
        HS3.add("Y");
        HS4.add("Z");

        System.out.println(HS3.toString());
        System.out.println(HS4.toString());

        System.out.println(HS3.contains("C"));

        System.out.println(HS4.containsAll(ll2));
        System.out.println(ll4.toString());
        ll4.poll();
        System.out.println(ll4.toString());
        System.out.println(HS4.toString());
        System.out.println(HS4.containsAll(ll4));

        HS4.addAll(ll3);

        System.out.println(HS4.toString());
        System.out.println(HS3.toString());
        HS4.removeAll(HS3);

        System.out.println(HS4.toString());

        for (String nums: HS3) {
            System.out.print(nums + " ");
        }
        System.out.println();

        MyIterator<String> itr6 = HS3.iterator();
        try {
            itr6.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        try {
            itr6.next();
            itr6.remove();
        }
        catch (Exception e) {
            System.out.println(e.toString());
        }

        while(itr6.hasNext()) {
            System.out.print(itr6.next() + " ");
        }
        System.out.println();

        System.out.println(HS3.toString());
        System.out.println(ll3.toString());
        HS3.retainAll(ll3);
        System.out.println(HS3.toString());

        ll3.clear();
        ll4.clear();

        System.out.println(ll3.toString());
    }
}
