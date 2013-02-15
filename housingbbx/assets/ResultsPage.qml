import bb.cascades 1.0

Page {
    property string title :titleBar.title 
    titleBar: TitleBar {
        id:titleBar
    
    }
    Container {
    }
    
    
    actions: [
    ActionItem {
        id: searchAction
        ActionBar.placement:ActionBarPlacement.OnBar
        onTriggered: searchSheet.open()
    }    
    ]
    
    
    attachedObjects: [
     
     SearchSheet {
         id:searchSheet
     }  
        
    ]

}
