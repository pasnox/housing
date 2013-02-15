import bb.cascades 1.0

Container {
    id:root
    property variant fields : new Array 
    property string title 
    property string description
    property bool pressed : false
    preferredHeight: 100
    background: pressed ? Color.Blue : Color.Gre
    
onTouch:  
        {    
                if ( event.isDown() ) 
        root.pressed = true;
                if (event.isCancel())
        root.pressed = false;   
                if (event.isUp() )
                {
                            root.pressed = false;
                }
        }
    
    gestureHandlers: [
        TapHandler {
            onTapped: {

                checkListSheet.open();
                

            
            }
        }
    
    
    ]
    
    
    
    onFieldsChanged: {
        checkListSheet.dataModel.clear();
        for (var i=0; i<fields.length; ++i)
        {
                    var item = new Object;
                    item.title = fields[i];
                    item.checked = false;
                    checkListSheet.dataModel.append(item);    
        } 
    }
    
    Divider { }
    Container {
        layout: DockLayout {  }
        horizontalAlignment: HorizontalAlignment.Fill
        Container {
            leftPadding: 20
            horizontalAlignment: HorizontalAlignment.Left
            Label {
                text: root.title
                textStyle.fontSize: FontSize.XLarge
            }
            
            Label {
                text: root.description
                textStyle.fontSize: FontSize.Small
                textStyle.color: Color.DarkGray
            }
        
        
        }
        ImageView {
            
            imageSource: "gfx/ic_next.png"
            horizontalAlignment: HorizontalAlignment.Right
        }
    }
    attachedObjects: [
        
        CheckListSheet {
            id:checkListSheet
            title: root.title 
            onClosed: {
                var desc = new Array;
                for ( var i=0; i< checkListSheet.dataModel.size(); ++i)
                  {
                                      if (checkListSheet.dataModel.value(i).checked == true)
                  desc.push(checkListSheet.dataModel.value(i).title);
                  }
                  
                  
                  description = desc.join(",");
            
            }
        }
    ]
}
