//chain of responsibility�� å�ӵ��� ����Ǿ� �־� ���� å���� �� �� �� ������
// ���� å���ڿ��� �ڵ����� �Ѿ�� ������ ���Ѵ�.(��ȭ �߰�)
#include <iostream>
#include <string>
using namespace std;

class HelpHandler
{
public:
	HelpHandler(HelpHandler* pObj = 0, string helpMsg = "")
	{
		pSuccessor_ = pObj;
		helpMsg_ = helpMsg;
	}
	virtual void SetHandler(HelpHandler* pObj, string helpMsg)
	{
		pSuccessor_ = pObj;
		helpMsg_ = helpMsg;
	}
	virtual bool HasHelp() { return !helpMsg_.empty(); }
	virtual void HandleHelp()
	{
		if (pSuccessor_)
			pSuccessor_->HandleHelp();
	}
	virtual void ShowHelpMsg()
	{
		//--helpMsg_�� �����ش�.
		cout << helpMsg_ << endl;
	}

protected:
	string helpMsg_;
private:
	HelpHandler * pSuccessor_;
};

class Widget : public HelpHandler
{
protected:
	Widget(Widget* pObj, string helpMsg = "") :HelpHandler(pObj, helpMsg)
	{
		pParent_ = pObj;
	}
private:
	Widget * pParent_;
};
class Button : public Widget
{
public:
	Button(Widget* pObj, string helpMsg = "") :Widget(pObj, helpMsg) {}
	virtual void HandleHelp()
	{
		if (HasHelp())ShowHelpMsg();
		else HelpHandler::HandleHelp();
	}
	virtual void ShowHelpMsg()
	{
		// --helpMsg_ ������ Button ���� ��Ŀ� ���߾� �����ش�.
		cout << helpMsg_ << endl;
	}
};

class Dialog :public Widget
{
public:
	Dialog(HelpHandler * pObj, string helpMsg = "") :Widget(0)
	{
		SetHandler(pObj, helpMsg);
	}
	virtual void HandleHelp()
	{
		if (HasHelp())ShowHelpMsg();
		else HelpHandler::HandleHelp();
	}
	virtual void ShowHelpMsg()
	{
		//--helpMsg_ ������ Dialog ���� ��Ŀ� ���߾� �����ش�.
		cout << helpMsg_ << endl;
	}
};

class Application : public HelpHandler
{
public:
	Application(string helpMsg): HelpHandler(0,helpMsg){}
	virtual void HandleHelp()
	{
		ShowHelpMsg();
	}
	virtual void ShowHelpMsg()
	{
		//--helpMsg_ ������ �����ش�.
		cout << helpMsg_ << endl;
	}
};

void main()
{
	Application *pApp = new Application("A[[lication Help");
	Dialog* pDialog = new Dialog(pApp, "Dialog Help");
	Button* pButton = new Button(pDialog);

	pButton->HandleHelp();
}