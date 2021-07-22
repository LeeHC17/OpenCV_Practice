연산량이 많기 때문에 Debug모드가 아닌 Release모드에서 실해해야 빠른 검출 결과를 확인할 수 있다.

## 실행 결과
![1](https://user-images.githubusercontent.com/76603802/126608028-affb07c3-2f9f-4355-be7e-df6ba43df364.jpg)

처음 실행하면 위와 같은 윈도우가 나온다.

![2](https://user-images.githubusercontent.com/76603802/126608051-acac54dd-1426-4f6f-a273-473eefbffdca.jpg)

윈도우에서 아무 버튼도 누르지 않고 "Play" 버튼을 누르면 opencv3.4.14/samples/data 에 저장되어 있는 vtest.avi 파일이 실행된다.

![3](https://user-images.githubusercontent.com/76603802/126608068-ae8b7db9-3908-467d-bf96-164614241f0b.jpg)

"People Detection" 체크박스를 체크하면 위의 사진과 같이아래에 두 라디오 버튼이 활성화 된다. Hog 알고리즘을 이용하여 보행자를 검출하기 위해 "Hog" 라디오 버튼을 체크한 후 "Play" 버튼을 누른다.

![4](https://user-images.githubusercontent.com/76603802/126608148-931517c2-f2aa-47bf-a373-4ae7671214de.jpg)

"People Detection"체크박스를 체크하고 "Hog" 라디오 버튼을 체크한 뒤 "Play" 버튼을 누르면 위와 같이 vtest.avi 파일에 나오는 보행자들을 초록색 사각형으로 표시해준다.

![5](https://user-images.githubusercontent.com/76603802/126608162-3f432f60-70b0-4574-8166-4c3492644c0f.jpg)

그 다음 haarcascade를 이용하여 보행자를 검출하기 위해 위와 같이 "People Detection" 체크박스가 체크된 상태에서 "Haarcascade" 라디오 버튼을 누른다.

![6](https://user-images.githubusercontent.com/76603802/126608176-ace0da61-3974-4feb-b0f8-643bf94cea09.jpg)

"People Detection" 체크박스를 체크하고 "Haarcascade" 라디오 버튼을 체크한 뒤 "Play" 버튼을 누르면 위와 같이 vtest.avi 파일에 나오는 보행자들을 초록색 사각형으로 표시해준다.

![1](https://user-images.githubusercontent.com/76603802/126608028-affb07c3-2f9f-4355-be7e-df6ba43df364.jpg)

"People Detection" 체크박스에 체크를 해제하면 아래에 두 라디오 버튼이 다시 비활성화된다.
