#include "WebHistory.hpp"

WebHistory::WebHistory()
{
    // Does nothing.
}

WebHistory::WebHistory(std::string historyText)
{
	// history = url timestamp | url timestamp | url timestamp...
    // urls are string and timestamps are non-negative integers.
    std::string delimiter = " | ";

	std::string tabInfo;
    std::string url;
    std::string timestamp;
    size_t pos = 0;

    while (true)
	{
        pos = historyText.find(delimiter);

        bool breakTheLoop = (pos == std::string::npos);

        tabInfo = historyText.substr(0, pos);
        historyText.erase(0, pos + delimiter.length());

        pos = tabInfo.find(" ");

        url = tabInfo.substr(0, pos);
        timestamp = tabInfo.substr(pos + 1, tabInfo.length() - pos);

		Node<Tab> *newPage = new Node<Tab>(Tab(url, std::atoi(timestamp.c_str())), NULL, NULL);
        insertInOrder(newPage);

        if (breakTheLoop)
		{
			break;
		}
    }
}

void WebHistory::printHistory()
{
	std::cout << "Your web history:" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << std::endl;
	if (history.getHead()->next == history.getTail())
	{
		std::cout << "History is empty." << std::endl;
		std::cout << std::endl;
	}
	else
	{
		Node<Tab> *node = history.getFirstNode();

		while (node != history.getTail())
		{
		    std::cout << "Page: " << node->element.getUrl() << std::endl;
			std::cout << "Last Visited: " << node->element.getTimestamp() << std::endl;
			std::cout << std::endl;
		    node = node->next;
		}
	}
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << std::endl;
}
using namespace std;
WebHistory::WebHistory(std::string url, int timestamp)
{
  Tab a(url,timestamp);
  history.insertAtTheFront(a);
}

void WebHistory::insertInOrder(Node<Tab> *newPage)
{
	Node<Tab> *tmp=history.getHead()->next;
  Node<Tab> *end=history.getTail();
  int givenTimeStamp=newPage->element.getTimestamp();
  int times=-1;
  while(tmp!=end){
    times=tmp->element.getTimestamp();
    if(times<=givenTimeStamp) break;
    tmp=tmp->next;
  }
  history.insertAfterGivenNode(newPage->element,tmp->prev);
  delete newPage;
}

void WebHistory::goToPage(std::string url, int timestamp)
{
	Node<Tab> *newPage = new Node<Tab>(Tab(url,timestamp),NULL,NULL);
  insertInOrder(newPage);
}

void WebHistory::clearHistory()
{
	history.removeAllNodes();
}

void WebHistory::clearHistory(int timestamp)
{
  Node<Tab> *tmp=history.getHead()->next;
  Node<Tab> *tmp2;
  Node<Tab> *end=history.getTail();
  while(tmp!=end){
    if(tmp->element.getTimestamp()<=timestamp) break;
    tmp=tmp->next;
  }
  while(tmp!=end){
    tmp2=tmp->next;
    history.removeNode(tmp);
    tmp=tmp2;
  }
}

WebHistory WebHistory::operator+(const WebHistory &rhs) const
{
  Node<Tab> *tmp;
  Node<Tab> *end;
  Node<Tab> *add;
	WebHistory res;
  res.history.getTail()->element.setTimestamp(-1);
  res.history.getHead()->element.setTimestamp(-1);
  for(tmp=history.getHead()->next,end=history.getTail();tmp!=end;tmp=tmp->next){
    res.goToPage(tmp->element.getUrl(),tmp->element.getTimestamp());
  }
  for(tmp=rhs.history.getHead()->next,end=rhs.history.getTail();tmp!=end;tmp=tmp->next){
    res.goToPage(tmp->element.getUrl(),tmp->element.getTimestamp());
  }
  return res;
}

int WebHistory::timesVisited(std::string pageName)
{
  int count=0;
  Node<Tab>* tmp;
  Node<Tab>*end;
	for( tmp=history.getHead(),end=history.getTail();tmp!=end;tmp=tmp->next){
    if(pageName==tmp->element.getWebSite()) count++;
  }
  return count;
}

std::string WebHistory::mostVisited()
{
  Node<Tab>* tmp;
  Node<Tab>*end;
  int tmpCount=0;
  int maxCount=0;
  string mostVisitedPage="";
  for(tmp=history.getHead(),end=history.getTail();tmp!=end;tmp=tmp->next){
    tmpCount=timesVisited(tmp->element.getWebSite());
    if(tmpCount>maxCount){
      maxCount=tmpCount;
      mostVisitedPage=tmp->element.getWebSite();
    }
  }
  return mostVisitedPage;
}
