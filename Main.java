import java.util.Scanner;


public class Main {
	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		
		LList list = new LList();
		int input = 0;
		
		while(input != 7){
			System.out.println("1. Append");
			System.out.println("2. Insert");
			System.out.println("3. Next");
			System.out.println("4. Print");
			System.out.println("5. Move to start");
			System.out.println("6. List length");
			System.out.println("7. Exit");
			System.out.print("Enter your choice: ");
			input = in.nextInt();
			
			switch(input){
				case 1:
					System.out.print("Enter data to append: ");
					list.append(in.nextInt());
					break;
				case 2:
					System.out.print("Enter data to insert: ");
					list.insert(in.nextInt());
					break;
				case 3:
					list.next();
					break;
				case 4:
					list.print();
					break;
				case 5:
					list.moveToStart();
					break;
				case 6:
					System.out.println("List size: " + list.getLength());
					break;
				case 7:
					System.out.println("Program Terminated!");
					break;
				default:
					System.out.println("Invalid! Choose again.");
					break;

			}
				
			
			
		}
		
		/*
		list.append(4);
		list.append(0);
		list.append(2);
		list.insert(1);
		list.next();
		list.insert(10);
		list.next();
		list.next();
		list.insert(5);
		list.print();
		System.out.println();
		System.out.println("size is " + list.getLength());*/
	}
}
