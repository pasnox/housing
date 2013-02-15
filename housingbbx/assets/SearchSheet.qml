import bb.cascades 1.0

Sheet {
    id:root
    Page {
        titleBar: TitleBar {
            title: "Search"
            acceptAction: ActionItem {
                title: "Search"
            }
            dismissAction: ActionItem {
                title: "Close"
                onTriggered: root.close();
            }
        }
        ScrollView {
            
            Container {
                Container {
                    leftPadding: 20
                    rightPadding: 20
                    topPadding: 20
                    
                    TextField {
                        inputMode: TextFieldInputMode.Text
                        autoFit: TextAutoFit.FitToBounds
                        input.submitKey: SubmitKey.Search
                    }
                }                
                Header {topMargin: 10; title: "Type"}
                RadioGroup {
                    dividersVisible: true
                    Option {
                        text: "Rent"
                    }
                    Option {
                        text: "Purchase"
                    }
                }
                
                Header {
                    title: "Options"
                }
                
                CheckListItem {
                    title: "Properties"
                    fields: ["hello", "sacha"]
                }
                CheckListItem {
                    title: "Rooms"
                    fields: ["hello", "sacha"]
                }
                CheckListItem {
                    title: "Bedrooms"
                    fields: ["hello", "sacha"]
                }
                
                Header {
                    title: "Budget"
                }
                Container {
                    leftPadding: 20
                    rightPadding: 20
                    topMargin: 20
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Container {
                        
                        TextField {
                            hintText: "min."
                            inputMode: TextFieldInputMode.NumericPassword
                        }
                    }
                    Container {
                 leftMargin: 20
                        TextField {
                            hintText: "max."
                            inputMode: TextFieldInputMode.NumericPassword
                        }
                    }
                }
            }
        
        }
    }
}