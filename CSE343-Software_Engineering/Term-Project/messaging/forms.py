from django import forms
from .models import Message

class MessageForm(forms.ModelForm):
    class Meta:
        model = Message
        fields = [
            'receiver',
            'topic',
            'message_text',
        ]

class MessagetoTrainerForm(forms.ModelForm):
    class Meta:
        model = Message
        fields = [
            'topic',
            'message_text',
        ]