
# SQL DATABASE

## Name: <ins> Ivan Flores </ins>

## Features:

- Not Implemented:
  - DELETE and DROP functionality
  

<br><br>

- Implemented:
  - INSERTION
  - CREATE / MAKE
  - SELECT
  - STORAGE OF RECORDS in .bin files
  - STROAGE OF TABLE COLUMNS IN .TXT FILE

- DATA STRUCTURES (CREATED BY ME AND USED IN THIS PROJECT)
  - B+ TREE
  - MULTIMAP
  - MAP
  - B TREE
  - QUEUE
  - STACK
  - LINKED LIST
  - NODE


<br><br>

- Bugs
  - NONE

<br><br>

# Reflections:

- In this SQL project, every data structure used was created by me with exception to vectors. This project took a total 4 months and a half to create. Within that time I learned and got a very good understanding of how datastructures such as Trees, Graphs and Maps work and the variations of all of them. It was very challenging considering how demanding C++ is and how sensitive it is to shitty code. In all, I'm very satisfied with how the SQL Database project turned out. Clone it, run the main and enjoy the SQL Database.

# HELP / DIRECTIONS
<pre>
<br/><br/><br/><br/>
<CREATE | MAKE> : {  <create | make> table <TABLE_NAME> fields <FIELD_NAME> [, <FIELD_NAME>...]  }
<INSERT> : { insert <INTO> <TABLE_NAME> values <VALUE> [, <VALUE>...]      }
<SELECT> : {  select <* | FIELD_NAME> [, ,FIELD_NAME>...]
					from <TABLE_NAME>
					where <FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>
						[<LOGICAL_OPERATOR>
							<FIELD_NAME> <RELATIONAL_OPERATOR> <VALUE>...]
			}

<VALUE>  : A string of alphanumeric characters, or a string of alphanumeric
 			characters and spaces enclosed by double quotation marks:
 			"Jean Luise", Finch, 1923
<RELATIONAL OPERATOR> : [ = | > | < | >= | <= ]
<LOGICAL OPERATOR>    : [and | or]
</pre>

