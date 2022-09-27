import java.sql.*;
import java.util.*;
public class connect {
	
	
	public static void main(String [] args) {
		try{  
				Class.forName("com.mysql.cj.jdbc.Driver");  
				Connection con=DriverManager.getConnection(  
				"jdbc:mysql://10.10.12.108:3306/te31144db","te31144","te31144");  
				//here sonoo is database name, root is username and password  
				Statement stmt=con.createStatement();  
				Scanner sc = new Scanner(System.in) ;				
				String table_name = "";
				ResultSet rs ;
				DatabaseMetaData dbm  = con.getMetaData() ;				
//				while(rs.next()) {
//					String table = rs.getString(1) ;
//					if(table == table_name) {
//						exists = true;
//						break ;
//					}
//					
//				}
//				if(! exists) {
				String query ="" ;
					
									
//				}
				while(true) {
					System.out.println("1)CREATE") ;
					System.out.println("2)INSERT") ;
					System.out.println("3)UPDATE") ;
					System.out.println("4)DELETE") ;
					System.out.println("5)DISPLAY") ;
					System.out.println("(-1 FOR END)") ;
					
					int ch ;
					System.out.println("Enter your choice") ;
					ch = sc.nextInt() ;
					if( ch == 1) {
						System.out.println("Enter table name") ;
						
						table_name = sc.next() ;
						ResultSet tables = dbm.getTables(null, null, table_name, null) ;
						boolean present = false ;
						if(tables.next()) {
							System.out.println("Table already exists") ;
							continue ;
						}
//						System.out.println("Here\n") ;
						int col = 0 ;
						System.out.println("Enter no of columns") ;
						col = sc.nextInt() ;
						String col_name = "" ;
						String  dtype = "" ;					
						query = "CREATE TABLE " + table_name + "( "  ;
						for(int i =1 ; i<= col ; ++ i) {
							System.out.println("Enter " + i + " column name ") ;
							col_name = sc.next();
							System.out.println("Enter datatype ") ;
							dtype =sc.next();
							query += col_name + " "  + dtype + "," ;
						}
						query = query.substring(0, query.length() -1) ;
						query += ")" ;
						 System.out.println("Your query is " + query) ;
		
						 stmt.executeUpdate(query) ;
						
						
					}
					else if( ch == 2) { 
						System.out.println("Enter table name in which you want to enter values") ;						
						table_name = sc.next() ;
						ResultSet tables = dbm.getTables(null, null, table_name, null) ;
						if(!tables.next()) {
							System.out.println("Table does not exist") ;
							continue ;
						}
						query = "SELECT * FROM "  ;
						query += table_name ;
						rs = stmt.executeQuery(query) ;
						ResultSetMetaData rsmd =rs.getMetaData() ;
						query ="INSERT INTO " + table_name + " VALUES ( " ;
						System.out.println("Enter values") ;
						int col = 0  ;
						col = rsmd.getColumnCount() ;
						for(int i = 1;  i <=col ; ++ i) {
							System.out.println("Enter "  + rsmd.getColumnName(i)) ;
							String dtype = rsmd.getColumnTypeName(i);			
							if(dtype.equals("INT")) {
								int intval ;
								intval = sc.nextInt() ;
								query += intval ;	
								query += ',' ;
							}
							else if(dtype.substring(0,7).equals("VARCHAR")) {
								String stringval ; 
								stringval = sc.next();
								query += '"' ;
								query += stringval ;
								query += '"' ;
								query += ',' ;
							}
						}
						
						query = query.substring(0 ,query.length() - 1) ;
						query += ")" ;
						System.out.println("Your query string is " + query) ;
						stmt.executeUpdate(query) ;
						
					}
						else if( ch == 3) {
							System.out.println("Enter table name in which you want to update values") ;						
							table_name = sc.next() ;
							ResultSet tables = dbm.getTables(null, null, table_name, null) ;
							if(!tables.next()) {
								System.out.println("Table does not exist") ;
								continue ;
							}
							query = "SELECT * FROM "  ;
							query += table_name ;
							rs = stmt.executeQuery(query) ;
							ResultSetMetaData rsmd =rs.getMetaData() ;
							int col = 0  ;
							col = rsmd.getColumnCount() ;
							String findrec ;
							System.out.println("Enter column name which you want to update") ;
							findrec =sc.next();
							String colname  ="" , newrectype ="" ;
							String unique ="" , uniqueval ;
							for(int i = 1 ; i <= col ; ++ i) {
//								System.out.println("Column name " + i + " = " + rsmd.getColumnName(i)) ;
								if(findrec.equals(rsmd.getColumnName(i))) {
									colname = rsmd.getColumnName(i) ;
									newrectype = rsmd.getColumnTypeName(i) ;									
									break ;
								}
							}
							System.out.println(colname) ;
							if(newrectype.equals("INT")) {
								query = "SELECT * FROM " +table_name  ;
								rs =stmt.executeQuery(query) ;
								uniqueval = rs.getString(1) ;
								unique = rsmd.getColumnName(1) ;
								int val ;
								System.out.println("Enter " + newrectype) ;
								val = sc.nextInt() ;
								query = "UPDATE TABLE " + table_name + " SET " + colname + "=" +val + " WHERE " + unique + "=" + uniqueval ;								
								stmt.executeQuery(query)	;
							}
							else if (newrectype.equals("VARCHAR")) {
								query = "SELECT * FROM " +table_name  ;
								rs =stmt.executeQuery(query) ;
								uniqueval = rs.getString(1) ;
								unique = rsmd.getColumnName(1) ;
								String  val ;
								System.out.println("Enter " + newrectype) ;
								val = sc.next() ;
								query = "UPDATE TABLE " + table_name + " SET " + colname + "=" +val + " WHERE " + unique + "=" + uniqueval ;
								stmt.executeQuery(query)	 ;
							}
							System.out.println("Your query string is " + query) ;
//							
							
						
						}
						else if (ch == 5 ) {
							System.out.println("Enter table name for which you want to display values") ;						
							table_name = sc.next() ;
							ResultSet tables = dbm.getTables(null, null, table_name, null) ;
							if(!tables.next()) {
								System.out.println("Table does not exist") ;
								continue ;
							}
							query = "SELECT * FROM " + table_name ;
							 rs = stmt.executeQuery(query) ;
							ResultSetMetaData rsmetadata = rs.getMetaData() ;
							 int count = rsmetadata.getColumnCount();
							 
							 System.out.print("\n") ;
					            // Step 6: Process the statements
					            for (int i = 1; i <= count; i++) {
					                System.out.print(rsmetadata.getColumnName(i)
					                                 + "\t");
					            }
					            System.out.println();
							while(rs.next()) {
								for(int i = 1;i<=count ; ++ i) {
									System.out.print(rs.getString(i) + "\t")  ;
								}
								System.out.print("\n") ;
							}
							System.out.print("\n") ;
						}
						else if (ch == -1) {
							System.out.println("Terminated") ;
							break ;
						}
				} 
		}
		catch(Exception e){ System.out.println(e);}  
			} 
}
