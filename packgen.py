import sys 
from PyQt5 import QtGui, QtCore
from PyQt5.QtGui import QColor, QPalette
from PyQt5.QtCore import QDate, QTime, QDateTime, Qt
from PyQt5.QtWidgets import QApplication, QWidget, QInputDialog, QLineEdit, QFileDialog, QMessageBox
from PyQt5.QtWidgets import* 
from PyQt5.uic import loadUi
import serial.tools.list_ports
from serial import SerialException
import serial
import struct
import os
import sys
import glob
from dataclasses import dataclass
import xml.etree.ElementTree as ET






class MyForm(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        loadUi("form.ui",self)
        
        #self.struct = list() 
        self.structs = list()
        self.gen_Button.clicked.connect(self.generate_pack)
        self.load_xml_Button.clicked.connect(self.load_xml_file)
        self.hfile_txt.setFont(QtGui.QFont('Arial', 15))
        self.cfile_txt.setFont(QtGui.QFont('Arial', 15))
        
        
    def var_type(self):
        
        pass
    def load_xml_file(self):
        options = QFileDialog.Options()
        options |= QFileDialog.DontUseNativeDialog
        self.app_file_location, _ = QFileDialog.getOpenFileName(self,"QFileDialog.getOpenFileName()", "","Python Files (*.xml);;All Files (*)", options=options)
        
        if self.app_file_location:
           self.xml_tree = ET.parse(self.app_file_location)
           self.parse_xml()
           
           
    def parse_xml(self):   
        if self.xml_tree :
            root = self.xml_tree.getroot()
            #structs 
            
            self.structs.clear()
            count =0
            for i in root: 
              struct = list()
              
              for j in i:
                  struct.append( (j.get('type'), j.get('name')) )
                  #print( (j.get('type'), j.get('name')) )
                  
              count +=1    
              self.structs.append(  (i.get('name'),struct) )
              
              

    
    
    def generate_pack(self):
        self.cfile_txt.setText("")
        self.hfile_txt.setText("")
        self.generate_cfile()
        self.generate_hfile()                       
             
    def generate_decode_handle(msg):
    
         return msg  
         
    def generate_encode_handle(msg):
        
        
         pass              
   
    def generate_cfile(self):
        msg = ""
        msg += "#include<packet.h>\n"
        
        msg += "#define PACK_SEND packet_send(uint8_t* data,uint16_t len);\n"
        for struct in self.structs:
            struct_name = struct[0]
            msg += "struct "+ struct_name +"_t" +"packet;\n"
        
        
        
        self.cfile_txt.setText(msg)
    

    
    
    
    def generate_hfile(self):
        
        msg = ""
        msg += "#ifndef __PACKET_H_ \n"
        msg += "#define __PACKET_H_ \n"
        msg += "#pragma pack(push,1)\n"
        #use loop to generate different packets
        #data type int8_t uint8_t int16_t uint16_t ... 
        for struct in self.structs:
            struct_name = struct[0]
            struct_vars = struct[1]
            msg += "\n"
            msg += "typedef struct "  + struct_name + "_struct{\n\n"

            for var in struct_vars:
                msg+="\t" + var[0] + " " + var[1]+ ";\n"
            msg += "\n}"+ struct_name +"_t;\n"
                
        msg += "\n"
        msg += "#pragma pack(pop)\n"
        msg += "\n"
        msg += "#endif\n"
        self.hfile_txt.setText(msg)







if __name__=="__main__":
    app = QApplication(sys.argv)
    ex=MyForm()
    ex.show()
    sys.exit(app.exec_())











