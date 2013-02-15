import bb.cascades 1.0
Sheet {
    id:root
    property alias title : titleBar.title
    property alias dataModel : model
    Page {
        titleBar: TitleBar {
            id:titleBar
            
            acceptAction: ActionItem {
                title: "Ok"
                onTriggered: root.close();
            }
        }
        
        ListView {
            horizontalAlignment: HorizontalAlignment.Fill
            
            dataModel: ArrayDataModel {  
                id:model 
            
            
            }
            
            
            listItemComponents: [
                ListItemComponent {
                    Container {
                        id: item
                        property int pressed 
                        horizontalAlignment: HorizontalAlignment.Fill
                        layout: StackLayout {  }
                        
                        // background: pressed  ? Color.Red : Color.White
                        
                        Container {
                            leftPadding: 20
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Left
                            layout: StackLayout { orientation: LayoutOrientation.LeftToRight     }
                            preferredHeight: 100
                            CheckBox {
                                checked: ListItemData.checked
                                verticalAlignment: VerticalAlignment.Center
                                onCheckedChanged: {
                                    if (!item.ListItem.initialized)return;
                                    var newItem = ListItemData;
                                    newItem.checked = checked;
                                    item.ListItem.view.dataModel.replace(item.ListItem.indexPath, newItem);
                                    // item.ListItem.data.checked = true;
                                }
                            }
                            Label {
                                leftMargin: 20
                                text: ListItemData.title
                                textStyle.base: SystemDefaults.TextStyles.TitleText
                                verticalAlignment: VerticalAlignment.Center
                            
                            
                            }
                        }
                        Divider {}
                        
                        onTouch:  
                     {    
                                                 if ( event.isDown() )  pressed = true;
                                                 if (event.isCancel())  pressed = false;   
                                                 if (event.isUp() ) pressed = false;
                     }  
                    }
                }
            ]
        
        
        
        }
    }
}
