# Double link list implementation

1) Build a doubly and circular linked list, which indicates the platforms of a trolley station.  
There are 20 platforms.  
You switch the platform you control with your joystick.  
The last platform is connected to the first platform, creating a loop.  
The target station of the platforms are initialized as “ “.  

Commands:  
>: Switch to the platform on the right.  
<: Switch to the platform on the left.  
+: Change the target station of the platform with “plus 1”.  
-: Change the target station of the platform with “minus 1”.  
The target station of the platforms can be: {(space), A, B, …, Z}.  
The station after Z is space. The station after space is A.  
Please treat “ “ as a valid input.  
.: Trolley departs from the platform to the target station under control.

2) Try to optimize the process. 

For example:  
input: EXPELLIA  
output: +++++.>---.--------.<.>----..---.>+.<+++++++++.-----.++++++++.--.  
 
