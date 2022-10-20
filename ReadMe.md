# WindowsApplicationByExample

该项目主要是为了加深Windows系统的消息机制，Windows应用程序的常用功能（如保存，键盘，绘制界面等）。学习书籍为《Microsoft Visual C++ Windows Applications By Example》（Stefan Bjornander）。该书我觉得很浅显易懂，前部分章节回顾了一些C++的基础知识，后面则以实际的MFC例子进行软件的搭建和讲解，主要例子有：**

## Ring

![image-20221020150632086](ReadMe.assets/image-20221020150632086.png)

该项目实现了在窗口中绘制圆形的功能，其中包含相关：

1. 鼠标消息
2. 序列化对象来保存绘制图形数据
3. 通过操作注册表来记录上一次画笔的颜色
4. 操作菜单栏来增加新的功能
5. 添加滑动条来增加视窗
6. 通过画盘来选择画笔颜色

### 重点

1. 记录每个圆的圆心坐标和颜色，每一次都进行重绘

```c++
void CRingView::OnDraw(CDC* pDC/*pDC*/)
{
	CRingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	PointArray& pointArray = pDoc->GetPointArray();
	ColorArray& colorArray = pDoc->GetColorArray();

	int iSize = (int)pointArray.GetSize();
	for (int i = 0; i < iSize; i++)
	{
		CPoint point = pointArray[i];
		COLORREF color = colorArray[i];

		CPen pen(PS_SOLID, 0, BLACK);
		CBrush brush(color);

		CPen* pOldPen = pDC->SelectObject(&pen);
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		pDC->Ellipse(point.x - RADIUS, point.y - RADIUS, point.x + RADIUS, point.y + RADIUS);

	}
}
```

2. 键盘消息绑定视图调整

```c++
void CRingView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_UP:
		OnVScroll(SB_LINEUP, 0, NULL);
		break;
	case VK_DOWN:
		OnVScroll(SB_LINEDOWN, 0, NULL);
		break;
	case VK_PRIOR:
		OnVScroll(SB_PAGEUP, 0, NULL);
		break;
	case VK_NEXT:
		OnVScroll(SB_PAGEDOWN, 0, NULL);
		break;
	case VK_LEFT:
		OnHScroll(SB_LINELEFT, 0, NULL);
		break;
	case VK_RIGHT:
		OnHScroll(SB_LINERIGHT, 0, NULL);
		break;
	case VK_HOME:
		OnHScroll(SB_LEFT, 0, NULL);	
		break;
	case VK_END:
		OnHScroll(SB_RIGHT, 0, NULL);
		break;
	default:
		break;
	}
}
```

3.序列化保存

```c++
void CRingDoc::Serialize(CArchive& ar)
{
	m_colorArray.Serialize(ar);
	m_pointArray.Serialize(ar);

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_nextColor; //to store << extraction
	}
	else
	{
		// TODO: add loading code here
		ar >> m_nextColor; //to load >> insertion
	}
}

```

4. 注册表记录上一次操作的画笔颜色

```c++
CRingDoc::CRingDoc() noexcept
{
	// TODO: add one-time construction code here
	m_nextColor = AfxGetApp()->GetProfileInt(_T("Ring"), _T("Color"), WHITE);

}

CRingDoc::~CRingDoc()
{
	AfxGetApp()->WriteProfileInt(_T("Ring"), _T("Color"), m_nextColor);
}
```

## Tetris

