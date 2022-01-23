from django import forms
from .models import Trainer, Comment

class TrainerForm(forms.ModelForm):

    class Meta:
        model = Trainer
        fields = [
            'Name',
            'Surname',
            'City',
            'Phone',
            'Gender',
            'Mail',
            'Address',
            'Work_Experience',
            'Birth_Date',
            'image'


        ]

class CommentForm(forms.ModelForm):
    class Meta:
        model = Comment
        fields = [
            'name',
            'content',
        ]
