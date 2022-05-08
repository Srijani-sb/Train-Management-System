# Train-Management-System

Implement the following system using a tree data structure (either AVL tree OR B-tree OR B+-tree) where every node represents a record of passenger name, passenger id, boarding train, boarding station, travelling class(Sleeper, 3AC, 2AC, 1AC), destination station, train id, Seat number (bogie number/seat number), and any other field you think that would be useful to passengers. You can also take a confirmation from the passenger whether upgrade of travel class is desired. 

The passenger id can be thought as a key and will represent a unique record in the database. The records should be always kept sorted according to the train id so that passengers boarding the same train have their data together.You can assume number of bogies of each class and number of seats in each bogie. 


Write the following functions : 

-insert

  • Insert a list of passengers and their details for the reservation
  
  • I/p parameters: Reservation request that includes a list of passenger names, passenger ids, boarding train, boarding station, travelling class(Sleeper, 3AC, 2AC,1AC), destination station, train id
  
  • O/P: Reservation done successfully, partially or the reservation failed.
  
  • Note – The set of passengers in a single reservation request should be allocated seats together. If all of them cannot get the seats together, then they need to be accommodated as close to each other in trains, that is, their bogie/seat numbers should be as close to each other.
  
-delete

  • Deletes an element if the passenger cancels the reservation.
  
  • I/p parameters: deleting all records of that particular passenger id.
  
  • O/p: If node gets deleted print Reservation cancelled successfully or if it gets failed then print Reservation Cancellation failed.
  
-getListDestination

  • Get the list of passengers having the same destination station and same train id
  
-SortByTravelDate

  • Input – Passenger id 
  
  • Output – Display the list of destination stations for a particular passenger as per the dates of the travel.
  
-SortTrains

  • I/p parameters: The train database with passenger data as given
  
  • O/p: Display the train number and the travel date in the sorted order of number of passengers on the train. 
  
-RangeSearch 

  o Given From-train-Number and To-Train-Number, display all the trains having train-number within the range defined by From-train-Number - To-Train-Number
