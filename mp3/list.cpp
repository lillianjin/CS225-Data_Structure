/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
    //during the loop, each node of the list is cleared from head to tail
    //while head is equal to tail, all the data is deleted
    if(tail!=NULL && head!=NULL)
    {
      while(head!=tail)
      {
        head = head->next;
        delete head->prev;
      }
    }
      //while list is empty
      else
      {
        length=0;
        return;
      }


    //delete the head and tail pointers and let them point to NULL
    delete tail;
    head=NULL;
    tail=NULL;
    length=0;

}


/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
    //create a new ListNode
    ListNode* a=new ListNode(ndata);

      //situation when list is not empty
    if(head!=NULL&&tail!=NULL)
    {
        a->next=head;
        head->prev=a;
        head=a;
        //a is a dynamic variable, will go out of scoup
        a=NULL;
    }

      //situation when list is empty
    else
    {
        a->prev=NULL;
        a->next=NULL;
        head=a;
        tail=a;
        a=NULL;
    }
      //length will increase by 1
    length++;
}



/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */

template <class T>
void List<T>::insertBack(T const& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* a=new ListNode(ndata);

      //situation when list is not empty
      if(head!=NULL&&tail!=NULL)
      {
        tail->next=a;
        a->prev=tail;
        tail=a;
        //a is a local variable, will go out of scoup
        a=NULL;
      }
      //situation when list is empty
      else
      {
        a->prev=NULL;
        a->next=NULL;
        head=a;
        tail=a;
        a=NULL;
      }
      //length will increase by 1
      length++;

}



/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    if(length == 0||head == tail)
    return;
    reverse(head, tail);
}


/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1
    //situation when the list is NULL
    if(startPoint == NULL || endPoint == NULL || startPoint == endPoint)
      return;

    //create copy of a startpoint, startPoint->next and startPoint->prev

    ListNode* startCopy = startPoint;
    ListNode* start_prev = startPoint->prev;
    ListNode* endCopy = endPoint;
    ListNode* end_next = endPoint->next;

    //reverse the prev and next pointers of each node
    //until startPoint meets endPoint

    while(startPoint!= endPoint)
    {
      ListNode* tempPoint = startPoint->prev;
      startPoint->prev = startPoint->next;
      startPoint->next = tempPoint;
      startPoint = startPoint->prev;
    }

    ListNode* tempPoint = startPoint->prev;
    startPoint->prev = start_prev;
    startPoint->next = tempPoint;
    endPoint = startCopy;
    endPoint->next = end_next;

    //set startPoint
    if(start_prev == NULL)
		  head = startPoint;
	  else
		  start_prev->next = startPoint;

    //set endPoint
	   if(end_next == NULL)
		   tail = endPoint;
	   else
		   end_next->prev = endPoint;
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
    if(length==0 || head==tail || n<=1)
      return;

    if(n>=length)
    {
      reverse(head, tail);
      return;
    }

    //find the exact startPoint and endpoint in each period
    //until the endPoint reaechs NULL

    ListNode* start = head;
	  ListNode* end = head;

    while(end->next!= NULL)
	{
		end = start;
    int num = 1;
		while(num < n && end->next!= NULL)
		{
			end = end->next;
      num++;
		}
		reverse(start, end);
		start = end->next;
	}

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if(head == NULL || head == tail || length <= 2)
      return;

      ListNode* curr = head;
      ListNode* end = tail;
      ListNode* temp = curr->next;

      while (temp != end && curr != end)
      {
        //move forward temp and curr for 1 unit
      	curr = curr->next;
      	temp = temp->next;

        //relink the node in front of and after curr
      	curr->prev->next = temp;
      	temp->prev = curr->prev;

        //put the extracted node to the end of the list
      	end->next = curr;
      	curr->prev = end;
      	curr->next=NULL;

        //rename the end contains curr
      	end = curr;

        //move curr to the old temp and move forward temp for 1 unit
      	curr = temp;
      	temp = temp->next;
      }

      tail=end;
}


/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2

    //special cases
    if(splitPoint<=0||start==NULL)
      return start;

      else
      {
        ListNode* tempstart=start;
        //start move the temp to where we start splitting
        for(int i=0; i<splitPoint; i++)
        {
          tempstart=tempstart->next;
        }

          ListNode* temp=tempstart->prev;
          tempstart->prev=NULL;
          temp->next=NULL;

          return tempstart; // change me!
    }

}




/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
  ListNode* tempfirst;
  ListNode* tempsecond;

  if(first==NULL)
  {
    return second;
  }

  else if(second==NULL)
  {
    return first;
  }

  //control the 1st node of first is always smaller than 1st node of second
  else if(second->data < first->data)
  {
    ListNode* temp=first;
    first=second;
    second=temp;
  }

  ListNode* firstnode=first;

  //compare first and second one by one
  while(first!=NULL && second!=NULL)
  {
    if(second->data < first->data)
    {
      tempfirst=first->prev;
      tempsecond=second;
      second=second->next;

      tempfirst->next=tempsecond;
      tempsecond->prev=tempfirst;
      tempsecond->next=first;
      first->prev=tempsecond;
    }

    /**else if(first->data < second->data && first->data == second->data && second->data < first->next->data && second->data == first->next->data)
    {
      second->next=first->next;
      first->next->prev=second;
      first->next=second;
      second->prev=first;
      first=first->next;
      second=second->next;
    }
    */

    else
      first=first->next;

    }


    //for the last node of first and second when second is longer than first

    if(second!= NULL)
    {
      //move to the last node of first list
      first = firstnode;
      while(first->next!=NULL)
        first=first->next;
      //link the rest of second to first
      first->next = second;
      second->prev = first;
    }
    /**
    if(first->next!=NULL)
    {
      first=first->next;
      first->prev = second;
      second->next = first;
    }
    */
    return firstnode;
  }




/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    if(chainLength <=1)
    {
       return start;
    }

    {
      ListNode *tempstart = split(start, chainLength/2);

      /**ListNode* tempstart=start;
      for(int i=0; i<chainLength/2; i++)
      {
        tempstart=tempstart->next;
      }
        ListNode* temp=tempstart->prev;
        tempstart->prev=NULL;
        temp->next=NULL;
        */

    	ListNode *part1 = mergesort(start, chainLength/2);
    	ListNode *part2 = mergesort(tempstart, chainLength-(chainLength/2));

    	return merge(part1, part2);
    }
}
