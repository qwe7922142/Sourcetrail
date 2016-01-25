#ifndef QT_CODE_AREA_H
#define QT_CODE_AREA_H

#include <memory>
#include <set>
#include <vector>

#include <QPlainTextEdit>

#include "utility/types.h"

class QDragMoveEvent;
class QPaintEvent;
class QResizeEvent;
class QSize;
class QtCodeFile;
class QtCodeSnippet;
class QtHighlighter;
class QWidget;
class TokenLocation;
class TokenLocationFile;

class MouseWheelOverScrollbarFilter
	: public QObject
{
	Q_OBJECT

public:
	MouseWheelOverScrollbarFilter(QObject* parent);

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};

class QtCodeArea
	: public QPlainTextEdit
{
	Q_OBJECT

public:
	class LineNumberArea
		: public QWidget
	{
	public:
		LineNumberArea(QtCodeArea* codeArea);
		virtual ~LineNumberArea();

		QSize sizeHint() const Q_DECL_OVERRIDE;

	protected:
		virtual void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

	private:
		QtCodeArea* m_codeArea;
	};

	static void clearAnnotationColors();

	QtCodeArea(
		uint startLineNumber,
		const std::string& code,
		std::shared_ptr<TokenLocationFile> locationFile,
		QtCodeFile* file,
		QtCodeSnippet* parent
	);
	virtual ~QtCodeArea();

	virtual QSize sizeHint() const Q_DECL_OVERRIDE;

	uint getStartLineNumber() const;
	uint getEndLineNumber() const;

	std::shared_ptr<TokenLocationFile> getTokenLocationFile() const;

	void lineNumberAreaPaintEvent(QPaintEvent* event);
	int lineNumberDigits() const;
	int lineNumberAreaWidth() const;
	void updateLineNumberAreaWidthForDigits(int digits);

	void updateContent();

	bool isActive() const;

	void setIsActiveFile(bool isActiveFile);

	QRectF getFirstActiveLineRect() const;

	std::string getCode() const;

protected:
	virtual void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
	virtual void showEvent(QShowEvent* event) Q_DECL_OVERRIDE;
	virtual void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
	virtual void enterEvent(QEvent* event) Q_DECL_OVERRIDE;
	virtual void leaveEvent(QEvent* event) Q_DECL_OVERRIDE;
	virtual void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	virtual void mouseDoubleClickEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	virtual void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	virtual void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

	virtual void contextMenuEvent(QContextMenuEvent* event) Q_DECL_OVERRIDE;

private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void updateLineNumberArea(const QRect&, int);
	void clearSelection();
	void setIDECursorPosition();

private:
	struct Annotation
	{
		int startLine;
		int endLine;

		int startCol;
		int endCol;

		int start;
		int end;

		Id tokenId;
		Id locationId;

		bool isScope;
		bool isError;

		bool isActive;
		bool isFocused;
	};

	struct AnnotationColor
	{
		std::string border;
		std::string fill;
	};

	std::vector<const Annotation*> getAnnotationsForPosition(int pos) const;

	void createAnnotations(std::shared_ptr<TokenLocationFile> locationFile);
	void annotateText();

	void setHoveredAnnotations(const std::vector<const Annotation*>& annotations);

	int toTextEditPosition(int lineNumber, int columnNumber) const;
	std::pair<int, int> toLineColumn(int textEditPosition) const;
	int startTextEditPosition() const;
	int endTextEditPosition() const;

	std::set<int> getActiveLineNumbers() const;

	std::vector<QRect> getCursorRectsForAnnotation(const Annotation& annotation) const;
	const AnnotationColor& getAnnotationColorForAnnotation(const Annotation& annotation);

	void createActions();

	static std::vector<AnnotationColor> s_annotationColors;

	QtCodeFile* m_fileWidget;

	QWidget* m_lineNumberArea;
	QtHighlighter* m_highlighter;

	const uint m_startLineNumber;
	const std::string m_code;

	std::shared_ptr<TokenLocationFile> m_locationFile;

	std::vector<Annotation> m_annotations;
	std::vector<const Annotation*> m_hoveredAnnotations;

	int m_digits;
	int m_panningValue; // just for horizontal panning

	QAction* m_setIDECursorPositionAction;
	QPoint m_eventPosition; // is needed for IDE cursor control via context menu
							// the position where the context menu is opened needs to be stored]

	bool m_isActiveFile;
};

#endif // QT_CODE_AREA_H
