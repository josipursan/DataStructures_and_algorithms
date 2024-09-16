# Notes

This .md file contains notes for hash notes from various sources : books, youtube video, online articles, etc.

## Source 1
https://www.youtube.com/watch?v=knV86FlSXJ8  

-hash tables represent a dynamic set of data  
-insert, delete and search is supported  
-search is a big advantage of hash tables (average = O(1); worst = O(n))  
-sometimes terms `hash table` and `dictionary` are used interchangeably  
&nbsp;&nbsp;&nbsp;-dictionary = generic way to map keys to values  
&nbsp;&nbsp;&nbsp;-hash tables = implementation of dict using hash values  


## Source 2  
https://www.youtube.com/watch?v=KyUTuwz_b7Q  
  
-widely used in databse indexing, caching, etc...  
-consider an ordinary 1D array - if we are searching for an element in the array, an ordinary linear
search can be quite time and resource consuming (depending on the array size)  
-if we knew the index of the element we are trying to retrieve from the array, we could simply look up the value :  
```Pseudocode
myData = Array(8); ---> this returns value 'Ada' we were looking for
```  
-if you know the index of the value you are trying to look up, time to retrieve is independent of the array size  
  
-but, **how can we know which array index contains the value we are looking for?**  
-each index number can be **calculated** using the value itself, meaning that the index number is related to the data  
-the video example disassembles names, adds ASCII values of each letter in the name, and modulo divides this value by the number of elements in the array --> **value gotten by modulo division represents the index where name value will be stored to array**  
&nbsp;&nbsp;&nbsp;-now when someone is searching for name 'Ada', our implementation will simply do the same thing to find index of 'Ada' in array, thus easily retrieving the value - however, is seems a bit counterintuitive retrieving a name you already now, but this concept is actually used to retrieve other data related to 'Ada' (e.g. we want to know where Ada works, what her D.O.B is, etc.)  
  
-the power of hash tables is they are used to store key-value pairs --> in our example 'Ada' would be the key, and her other data, such as D.O.B, address, employer, wold be the value(s)  
  
-*hashing algorithm* - the calculation applied to a key (might be a very large number, or a very large string) to transform it into a relatively small index number that corresponds to the position in the hash table where some data relevant to the key is stored  
  
**-collision** - when a hashing algorithm generates the same index for two different keys  
&nbsp;&nbsp;&nbsp;-naturally, two different keys can't be stored in the same array position (index)  
**-open addressing** - resolving a collision by placing an item to some index other than the calculated one  
&nbsp;&nbsp;&nbsp;-the name *open addressing* comes from the fact that any address is *open* to any item  
&nbsp;&nbsp;&nbsp;-**linear probing** - open addressing method which uses linear search to place an item for which index collision has occured (you basically move one index at a time from the calculated index until you find an emtpy spot where values for the given key can be place)  
  
**-load factor** - ratio of the total number of items stored and the size of the array  
&nbsp;&nbsp;&nbsp;-why is this used? Because often times collisions will happen, and by taking up space for an array that is larger than the total number of elements, we are making sure we've accomodated enough space for all of the elements, no matter their collisions  
&nbsp;&nbsp;&nbsp;-array can also be resized based on the load factor, meaning that if a certain load factor threshold has been surpassed, array is assigned more memory to accomodate further elements  
  
-as long as the load factor reasonably low, open addressing with linear probing shold work reasonably well  
  
**-chaining** - often called **closed addressing**  
&nbsp;&nbsp;&nbsp;-another way of solving collisions  
&nbsp;&nbsp;&nbsp;-now each place in the array is not storing values of a given key - instead it stores a pointer to the first element of a linked list  
&nbsp;&nbsp;&nbsp;-now when a collision occurs, this new value element will be added to the same index that is already being used, but because we are using a linked list, the already present element will be used to point us from itself, to the new value element we want to save at the calculated index  
&nbsp;&nbsp;&nbsp;-e.g. : index = 4 has been calculated for some key, but a value is already stored here. We will then create a new linked list node, store the necessary value in it. Then we will enter index = 4 and reach the already existing linked list node there, and points its node->next pointer to our newly created linked list node for our new value.  
```Pseudocode
array[4] ---> linkedListNode_previouslyCreated

newKey_index = hashingAlgorithm(newKey) = 4 ---> this is the same index as above

newKey_value_linkedListNode = linkedListNode(newKey_value)

array[4] ---> linkedListNode_previouslyCreated->next = newKey_value_linkedListNode

Final status : 
array[4] ---> linkedListNode_previouslyCreated ---> newKey_value_linkedListNode
```  
  
-linear probing can result in **primary clustering**  
&nbsp;&nbsp;&nbsp;-this means that keys bunch up in the array (because of the linear search)  
&nbsp;&nbsp;&nbsp;-there are alternatives to linear probing  
&nbsp;&nbsp;&nbsp;**-plus 3 rehash** - looking at every third slot along, until a free space is found  
&nbsp;&nbsp;&nbsp;**-quadratic probing** - squares the number of failed attempts when it is deciding how for along from the original point of collision to look for possible empty spaces  
&nbsp;&nbsp;&nbsp;**-double hashing** - applies a second hash function to the key when a collision occurs; the result of the second hashing function gives the number of how many positions we need to move from the original collision position to try and place the new value  
  
-the goal of each function is to minimze collisions, to provide a uniform distribution of hash values, should be easy to compute, and the algorithm should be capable of solving any collision