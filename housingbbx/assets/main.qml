// Default empty project template
import bb.cascades 1.0

// creates one page with a label
TabbedPane {
    
    Tab{
        title: content.title
        ResultsPage {
            title: "SeLoger.com"
        }  
    }
    
    Tab{
        title: content.title
        ResultsPage {
            title: "ChezMoi.com"
        }  
    }


}

