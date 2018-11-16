//STL

//#include <iostream> 앞으로 많이 쓸 헤더..
//#include <string>
//#include <vector>
//#include <list>
//#include <map>
//#include <set>
//#include <algorithm>
//#include <functional> 함수 객체.
//#include <iterator>

//set = 같은 종류 갯수 카운팅 , 갯수 상관없이 종류별 카운팅. 용이.
//set = 중복된 데이터 입력불가
//set 특성상 많은 함수가 지원 안함

//cbegin() c=const

//multiset = 중복데이터 입력가능, 기본정렬이 되서 입력된다.

//for_each(mesetList.begin(),mesetList.end(),fucn());
// 함수까지 같이 포함하여 for문으로 돌릴수 있음

//mem-fun =클래스 안의 멤버함수를 주소를 넘겨서 호출.
//bind2nd = 기본적으론 인자값을 한개,구조체 사용시 여러개 


//generate()

//std::map<int, string>  =사전식 자료관리. 반드시 인덱스가 있어야한다 (차례가 있어야한다)
//PAIR=값+키   //키=인덱스//키와 값이 같이다니는게 MAP// 유일성=키
//insert(make.pair(0,"홍길동"));
//first =키 //값=second
// 트리형식 - 검색을 빠르게 하려고.

//map 검색 // iter= mapList.find(100);

//힙 정렬 = 트리
//가장 우선순위가 높은걸 제일 앞으로 ..
//우선순위큐


// 깊이 우선 탐색은 스택
// 넓이 우선 탐색은 큐
// 로직은 항상 똑같아야 한다.


//크루스칼
//프림
//사이클은 피해라
//최소 비용 신장 트리
//최단 거리 계산 할때
//하지만 동적일때는 매우 불--편
//이거보다 좋은건 다이스타 알고리즘


//shared_ptr 스마트 포인터
//unique_ptr

//API
// 콘솔응 void, int main()
// API는 int WINAPI WinMain
// 인스턴스 - 메모리 실체

//윈도우 프로시저에는 함수 주소값를 넘겨주어야한다 .


//1프레임의 경과 시간
//1초의 프레임 카운터
//게임이 실행된 누적시간


//API
// bool init()
// bool Frame()
// bool Render()
// bool Release()
// 항상 있어야 하는 함수
